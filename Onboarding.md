# 🚀 Project Onboarding & Task Breakdown

Welcome to CE4703 Assignment #2!  
This document breaks down all tasks, deliverables, deadlines, and instructions for each team role.

---

# 🔧 Phase Breakdown (High-Level)

| Phase       | Description                                     |
|-------------|-------------------------------------------------|
| **Phase 1** | Card Structure + CardDeck base implementation   |
| **Phase 2** | Deck operations + sorting algorithm             |
| **Phase 3** | Game logic                                      |
| **Phase 4** | Integration + testing                           |
| **Phase 5** | Doxygen + final polishing                       |

---

# 🧑‍💻 Detailed Role Tasks

---

## 🎴 **Role 1 – Card Structure Developer**

### Tasks
- Create `enum Suit` (Club, Spade, Heart, Diamond)
- Create `enum Rank` (Two–Ace)
- Define `struct Card { Suit suit; Rank rank; }`
- Add helper functions:
  - `printCard()`
  - `compareCards()` if needed
- Add Doxygen comments

### Deliverables
- `card.h`
- `card.c`
- Clean enums + print functionality

### Deadline
End of Week 1.

---

## 🃏 **Role 2 – Deck Developer**

### Tasks
- Create `struct CardDeck` using dynamic memory:
  - Linked list **or** dynamic array — your choice
- Implement operations:
  - `initDeck(num_packs)`
  - `shuffleDeck()`
  - `addCard()`
  - `removeTopCard()`
  - `removeCardAt(position)`
  - `isEmpty()`
- Add Doxygen comments

### Deliverables
- `deck.h`
- `deck.c`

### Deadline
Mid Week 2.

---

## 🔄 **Role 3 – Sorting Developer**

### Tasks
- Choose sorting algorithm:
  - Bubble Sort (easy)
  - Insertion Sort (medium)
  - Merge Sort (hard but sexy)
- Implement:
  - `sortDeck(CardDeck *deck)`
- Integrate with the CardDeck structure
- Add Doxygen comments

### Deliverables
- Sorting code inside `deck.c` or separate file

### Deadline
End of Week 2.

---

## 🎮 **Role 4 – Game Logic Developer**

### Tasks
- Prompt user for number of packs
- Create hidden deck (shuffled)
- Create played deck + player decks
- Deal cards (8 each)
- Sort player decks
- Print hands
- Execute game loop:
  - Flip top hidden card
  - Alternate between players:
    - If match → play card
    - If no match → draw card & resort
  - If hidden deck empty → recycle played cards
- Detect win condition
- Display all actions

### Deliverables
- `main.c`
- Fully working game loop

### Deadline
Week 3 (priority).

---

## 🧪 **Role 5 – QA + Documentation**

### Tasks
- Test each file
- Integrate all code into final build
- Write Doxygen configuration
- Generate HTML docs
- Fix formatting (K&R style)
- Assemble final ZIP for submission

### Deliverables
- `/docs/` folder
- Final `.zip`

### Deadline
3 days before submission.

---

# 📅 Suggested Schedule

| Week | Goal |
|------|------|
| Week 1 | Card + Deck base done |
| Week 2 | Sorting + deck ops done |
| Week 3 | Game logic done |
| Week 4 | Testing + Doxygen + polish |

---

# 🛠️ Coding Style (Required)

- **K&R braces**
- **Meaningful function names**
- **One responsibility per function**
- **Document everything with Doxygen**

---

# 👍 Final Notes

- Always **pull before working**
- Commit small changes
- Ask questions early  
- Coordinate merges to avoid conflicts

Let’s get this bread.
