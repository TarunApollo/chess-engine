# Skill Mastery: Board Representation (Bitboards)

**Status:** DAY 1 — ATOMIC CONCEPTS. Working mode: **code-first**. Start writing
`board.h` / `board.c` directly — the Deep Dive Challenges below are on-demand
reference, not a gate. Pull one up when you hit a design decision you can't justify
to yourself, or when I flag that a Micro-Drill result exposes a gap. Day 2 (pattern
problems) still won't open until the six Micro-Drills exist and you can defend them
under questioning — but the order you get there is yours.

Scope of this file is deliberately narrow: **representation only** — the struct, the
encoding, the bit mechanics. Move generation, attack tables, and make/unmake are
later mastery files. Do not let your drills reach ahead into move generation.

---

## Concept 1 — Bitboard as a Set Representation

**Deep Dive Challenge**

Your own Systems Programming retake material (Exercise 13, `cset`) already forced you
to build a compact set over a bounded universe `{0,...,n-1}` using a bitvector, with
`O(1)` insert/delete/find and `O(n)` union/intersection. A chess board is exactly the
universe `{0,...,63}`.

Answer, precisely, not superficially:

1. If you represented the board as `enum piece board[8][8]` instead, name **three**
   distinct queries a search function performs at *every single node* (not once per
   game — once per node, potentially millions of times per second) that go from
   `O(1)` under a bitboard set representation to something worse under the array
   representation. Be specific about what "worse" means for each (linear scan? need
   to touch 64 cells?).
2. A `uint64_t` is simultaneously: a *number*, a *set*, and a *bit-indexed boolean
   vector*. State which of these three mental models is the correct one to hold in
   your head when you write `white_pawns & black_pieces`, and justify why treating
   it as "a number" would actively mislead you here.
3. What is the set-theoretic operation corresponding to each of: `&`, `|`, `^`, `~`,
   and `<<`? Give the chess-relevant meaning of each (e.g., "all squares occupied by
   *either* white or black" is which operator?).

**Micro-Drill**

Do not use loops. Implement these three functions against a single `uint64_t`-backed
set abstraction:

```c
int  set_contains(uint64_t set, int elem);      /* elem in [0,63] */
uint64_t set_add(uint64_t set, int elem);       /* returns new set */
uint64_t set_remove(uint64_t set, int elem);    /* returns new set */
```

State, in a comment above each function, its time complexity and *why* it is that
complexity given the hardware operations involved.

---

## Concept 2 — Square Indexing Scheme (Encoding Design)

**Deep Dive Challenge**

Research at chessprogramming.org (or equivalent primary sources) the dominant square
numbering conventions used in real bitboard engines — in particular **Little-Endian
Rank-File Mapping (LERF)**.

1. Under LERF, what square index is a1? What index is h8? Derive the general formula
   relating `(file, rank)` to a square index, and state it precisely.
2. This is not an arbitrary choice. Explain concretely: if you shift a bitboard of
   white pawns left by 8 bits (`<< 8`), what chess-meaningful operation does that
   perform *only if* your numbering convention is LERF? What would go wrong (in what
   direction would pieces incorrectly move) if you had instead chosen a
   row-major-from-h8 convention?
3. Shifting a bitboard east (`<< 1`) or west (`>> 1`) has a subtle bug waiting for
   anyone who does it carelessly. What is it, and which file(s) does it corrupt if
   you don't mask against it? (You do not need to fix it yet — just identify the
   failure precisely, in terms of which bits wrap around and why.)

**Micro-Drill**

Using **pure arithmetic only** — no lookup tables:

```c
int square_index(int file, int rank);  /* file, rank in [0,7] -> square in [0,63] */
int file_of(int square);               /* inverse component 1 */
int rank_of(int square);               /* inverse component 2 */
```

Then write a tiny driver in `main` that round-trips all 64 squares
(`square_index(file_of(sq), rank_of(sq)) == sq` for every `sq` in `[0,63]`) and
prints a single line confirming success or naming the first square that fails.

---

## Concept 3 — Struct Composition and Derived/Redundant State

**Deep Dive Challenge**

A working bitboard engine stores **both**: 12 per-piece-per-color bitboards (6 piece
types × 2 colors) **and** aggregate bitboards (`occupied[WHITE]`, `occupied[BLACK]`,
`all_occupied`). The aggregates are fully *derivable* from the 12 base bitboards — 
storing them is redundant in the strict information-theoretic sense.

1. Justify, from a systems-programming performance standpoint, why a real engine
   still stores and maintains this redundant state rather than recomputing
   `occupied[WHITE]` by OR-ing 6 bitboards every time it's needed. Quantify: how many
   times per search node would that recomputation happen if you didn't cache it?
2. The moment you introduce redundant derived state, you introduce an **invariant**
   that every mutating function must now preserve. State that invariant precisely
   (as a logical proposition relating the 12 base bitboards to the 3 aggregates).
3. What concrete, observable bug occurs during search if some future function (e.g.
   your move-maker, weeks from now) updates a piece bitboard but forgets to update
   the aggregate? Will it crash, or will it silently produce wrong answers? Which is
   worse for a chess engine and why?

**Micro-Drill**

Given (you write this struct yourself — this drill assumes it exists):

```c
typedef struct board {
    uint64_t pieces[2][6];     /* [color][piece_type] */
    uint64_t occupied[2];      /* derived */
    uint64_t all;               /* derived */
} Board;
```

Implement:

```c
void recompute_occupancy(Board *b);
```

Purely with bitwise OR over the 12 base bitboards. In a comment, state its time
complexity and confirm it is *constant* — explain why 12 fixed OR operations count
as O(1) and not O(n).

---

## Concept 4 — Unsigned Semantics and Shift Undefined Behavior

**Deep Dive Challenge**

C17 §6.5.7 specifies that if the right operand of a shift is negative, or is greater
than or equal to the width in bits of the (promoted) left operand, the behavior is
**undefined** — not "does something weird," undefined in the strict standardese
sense.

1. What is the maximum legal value of `sq` you may pass to `1ULL << sq` for a 64-bit
   board? What happens at exactly that boundary — is it legal or already UB?
2. Research what x86-64's `SHL` instruction actually does with a shift count that
   exceeds the operand width (hint: it masks the count against the operand's bit
   width in a specific way). Explain concretely what garbage value `1ULL << 64` is
   likely to silently produce on your machine — and why relying on this observed
   behavior instead of the standard is a trap.
3. Why must the literal be `1ULL` and not `1` when computing `1ULL << sq` for `sq`
   up to 63? What UB or silent truncation occurs with plain `1`, and on what kind of
   platform would it bite you?

**Micro-Drill**

```c
void set_bit(uint64_t *bb, int sq);
void clear_bit(uint64_t *bb, int sq);
```

Both must defensively `assert()` the precondition on `sq` *before* performing the
shift — not after. State in a comment why the assert must come first.

---

## Concept 5 — Bit Scanning (Enumerating Set Bits)

**Deep Dive Challenge**

A search function must enumerate every piece of a given type/color at every node —
i.e., walk the set bits of a bitboard one at a time.

1. Compare, precisely, the worst-case and average-case operation counts of: (a) a
   naive loop testing all 64 bit positions, (b) the "isolate lowest set bit" trick
   using `bb & -bb` combined with `bb &= bb - 1` to clear it, and (c) a hardware
   bit-scan builtin such as `__builtin_ctzll`.
2. Explain, algebraically, *why* `bb & -bb` isolates exactly the lowest set bit.
   (Hint: reason about two's-complement negation as `~bb + 1` and what happens at
   the position of the lowest set bit versus every bit below and above it.)
3. Why does the *right* choice between (a), (b), and (c) depend on how many bits are
   typically set — i.e., why is this a different tradeoff for a bitboard of all 8
   pawns versus a bitboard of a single king?

**Micro-Drill**

```c
int pop_lsb(uint64_t *bb);
```

Returns the index of the least-significant set bit and clears that bit from `*bb`.
Implement it using **only the mathematical trick from question 2 above** — no
`__builtin_ctzll`, no loop. Decide yourself what it should return when `*bb == 0`,
and defend that choice in a comment.

---

## Concept 6 — Population Count

**Deep Dive Challenge**

1. State Brian Kernighan's bit-counting algorithm's loop invariant precisely: what
   quantity strictly decreases each iteration, and why does that guarantee the loop
   terminates in *exactly* `popcount(x)` iterations rather than a fixed 64?
2. Contrast with a hardware `POPCNT` instruction (exposed via
   `__builtin_popcountll`): what is the complexity difference, and given that a
   chess engine may call popcount on the order of millions of times per second
   during search (material counts, mobility counts, etc.), why does this difference
   matter in practice even though both are "fast" in absolute terms?

**Micro-Drill**

Implement both, in the same file, so they can later be benchmarked against each
other:

```c
int popcount_kernighan(uint64_t bb);   /* Kernighan's algorithm, loop-based */
int popcount_builtin(uint64_t bb);     /* wraps __builtin_popcountll */
```

---

## Progression Gate — Day 1 → Day 2

Before Day 2 is issued, you must, for **each** of the six concepts above:

- Explain the concept in your own words (not a restated definition — demonstrate
  reasoning about *why*, not just *what*).
- Answer every Deep Dive Challenge sub-question.
- Have working, compiling code for every Micro-Drill, and be able to trace through
  it by hand (what does `pop_lsb` do, bit by bit, on a concrete example bitboard?).

Bring your answers and code back one concept at a time or all six at once — your
choice. I will interrogate weak spots before anything advances. No code will be
written for you; I will only ask questions until the gap closes.
