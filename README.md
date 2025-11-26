# CE4703 – Assignment 2: Card Game

This is the group repository for **CE4703 Assignment #2**.  
We will build a simple card game in C using:

- Visual Studio Community (Windows)
- Dynamic data structures
- Doxygen documentation
- Git for version control

This README contains all project instructions, team roles, setup steps, and workflow guidelines.

---

## 📌 Project Overview

We are building a card game in C for two players:

- Card structure with enums for suit + rank  
- Dynamic CardDeck structure (linked list or dynamic array)  
- Deck operations (shuffle, sort, add, remove...)  
- Game simulation according to the assignment rules  
- Full Doxygen comments  
- Must compile on **Visual Studio Community**  

---

## 🧩 Group Roles

| Role | Description																															|
|------|----------------------------------------------------------------------------------------------------------------------------------------|
| **1. |Card Structure Developer** | Implement `Card` struct + `enum Suit` and `enum Rank`. Add print functions + Doxygen.						|
| **2. |Deck Developer** | Implement dynamic `CardDeck`, linked list or malloc-based structure. Implement add/remove/shuffle/export functions.	|
| **3. |Sorting Developer** | Implement chosen sorting algorithm (Merge Sort, Bubble Sort, or Insertion Sort). Integrate with CardDeck.			|
| **4. |Game Logic Developer** | Implement the full game simulation and connect everything together.												|
| **5. |QA + Documentation** | Test the project, integrate components, add Doxygen + final polish.												|

---

## 🛠️ Development Environment

We **must** use:  
👉 *Visual Studio Community (Windows)*

We **store the code** in:  
👉 *This GitHub repository*

Workflow:

1. Clone repo locally  
2. Open Visual Studio  
3. Create a new “Empty C Project” **inside the cloned repo folder**  
4. Commit & push changes through Visual Studio Git tools  

Do **NOT** create the VS project outside the repo.

---

## 🧪 Build Instructions

1. Open the `.sln` file in Visual Studio  
2. Build Solution (Ctrl + Shift + B)  
3. Run the program  

---

## 📘 Doxygen Documentation

We will use Doxygen to generate HTML documentation.

To generate docs:

1. Install Doxygen  
2. Run:  
	doxygen -g Doxyfile
3. Open `/docs/html/index.html` in a browser.

---

## 🚀 Git Workflow (Quick)

- **Pull first**  
- Make changes  
- **Commit small chunks** (with useful messages)  
- **Push often**  

---

## 📅 Deadlines

We aim to finish before the module deadline.  
Each role has its own task list — see *Onboarding.md*.

---

## 📎 Links

- Visual Studio Community: https://visualstudio.microsoft.com/vs/community/
- Git for Windows: https://git-scm.com/downloads
- Doxygen: https://www.doxygen.nl/

---

## 🧑‍💻 Team Notes

Please keep coding style consistent (K&R style).  
Ask questions early — no one is expected to know everything.

Let’s lock in.
