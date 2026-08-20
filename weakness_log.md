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
