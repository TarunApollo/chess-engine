# Weakness Log

Tracks recurring conceptual and C-specific weaknesses across the chess engine
project. Entries are never removed on a single correct answer — only after
consistent, repeated demonstration of correction across multiple problems.

Format per entry: **Label** — Evidence — Corrective drill — Status.

---

## Baseline (2026-08-20)

No submissions yet. Log initialized at the start of `board_representation`
(see [skill_mastery_board_representation.md](skill_mastery_board_representation.md)).

Known risk factors going in (not yet evidenced weaknesses — just context to watch
for, given this is the user's first project of this kind):

- First time working with bitboards / bit-level set representations in C —
  watch for confusing "number" vs "set" mental models (Concept 1).
- First time the exam's `cset`-style bitvector pattern is applied to a live,
  performance-sensitive system rather than an isolated exercise — watch for
  under-justifying *why* O(1) operations matter at search-node frequency.
- No evidenced C memory/pointer mistakes yet — nothing to log until code is
  produced and reviewed.

*(This section will be replaced by dated, evidenced entries as drills are
submitted.)*

---

## Entry 1 (2026-08-20) — Tutorial-copied code run without independent verification

**Evidence:** `makefile` and `src/bitboard.c` were transcribed from Maksim Korzh's
YouTube bitboard-engine series. Two lines were copied without being independently
understood:
- `gcc -oFast ...` — a typo for `-Ofast` (capital O, optimization level) that
  actually parses as `-o Fast` (output-file flag). It happened to be harmless here
  only because a second, later `-o src/bitboard` silently overrode it — pure luck
  of argument order, not intent.
- `getchar()` at the end of `main` — copied without stating what problem it solves
  (Windows console-closes-on-exit behavior) or whether that problem applies here.

Once flagged, the user correctly reasoned through the `-o`-flag collision by running
gcc empirically rather than guessing — that recovery was solid.

**Corrective drill:** Before running any tutorial-sourced line of code or build
command going forward, state in one sentence what it does and why it's there,
*before* running it — not after something looks wrong. If the answer is "the video
did it," stop and look it up first.

**Status:** OPEN. Watch for repeat across future tutorial-derived commits — close
after two consecutive submissions where copied lines are pre-annotated with their
purpose.
