# 🧭 Git & GitHub Guide for Visual Studio Community

This guide explains how to use Git inside Visual Studio to collaborate on this project.

---

# 1. Install Requirements

### ✔ Install Git for Windows  
https://git-scm.com/downloads

### ✔ Install Visual Studio Community  
Make sure to select **Desktop Development with C++** workload.

---

# 2. Cloning the Repository

1. Go to our GitHub repo  
2. Copy the **HTTPS clone link**  
3. Open **Visual Studio**  
4. Go to:  
   **Git → Clone Repository**  
5. Paste the link  
6. Choose a folder  
7. Click **Clone**

The repo will now appear inside Visual Studio.

---

# 3. Create the Project INSIDE the Repo

1. In VS:  
   **File → New → Project**
2. Choose:  
   **Empty C++ Project** (yes, it runs C)
3. **IMPORTANT:**  
   Set the project location **inside the cloned repo folder**  
4. Click **Create**

Now the `.sln` file and source folders belong to Git.

(i alr did this step, so you can skip it)
---

# 4. Making Changes

Add `.c` and `.h` files under:
	Source Files
	Header Files
	
---

# 5. Committing Code

1. Open **Git Changes** panel  
   (bottom right or View → Git Changes)
2. Stage files  
3. Write a commit message  
4. Click **Commit & Push**

---

# 6. Pulling Updates

Before working:
- Click **Pull**  
  OR  
  **Git → Pull**  

Do this *every time* you open VS.

---

# 7. Resolving Conflicts

If VS detects overlapping edits:
- It will show conflict indicators  
- Choose which version to keep  
- Commit & push after resolving

---

# 8. Creating Branches (Optional)

To avoid clashes:
- Create branch per feature  
- Merge into `main` when done  

VS GUI makes this very easy.

---

# 9. Summary Workflow

1. Pull  
2. Make changes  
3. Commit small chunks  
4. Push  
5. Repeat  

---

# 🎉 You're ready to collaborate.
