## Game Description

**The Last Escape** is a 2D side-scrolling stealth, detection, puzzle, and action game developed using the **iGraphics** library with **C/C++**.

The game follows a character who witnesses a group of people involved in illegal activities at a railway station. After being discovered, the character is captured and thrown into prison. The player must escape from the prison, collect evidence, confront the criminals, and finally reach the police station to expose the truth.

The game combines exploration, puzzles, stealth, combat, shooting, and runner-style gameplay across three levels.

---

## Story

The player is walking through a railway station when they notice several people involved in illegal activities and loading illegal goods onto a train.

After being discovered, the player is captured and thrown into prison.

To escape and expose the criminals, the player must:

1. **Escape the prison cell.**
2. **Collect evidence against the criminals.**
3. **Reach the police with the evidence and bring the criminals to justice.**

---

## Game Structure

The game consists of **three main levels**, and each level contains different challenges and mini-games.

### Level 1 — BreakOut

The player starts inside a prison and must find a way to escape.

**Main Challenges:**

* Memory Puzzle to unlock the cell.
* Number Puzzle to escape the guard.
* Switch Puzzle to disable the CCTV.
* Falling Box mini-game.

**Rooms:**

1. **Room 1:** Escape the Cell
2. **Room 2:** Disable CCTV
3. **Room 3:** Proceed to the Investigation Room

---

### Level 2 — The Hidden File
After escaping, the player must collect evidence that can help expose the criminals.

**Main Challenges:**

* USB Hunt / Match-3 style mini-game.
* Room Number and Evidence Page Puzzle.
* Collecting and joining page pieces.
* Vault / Laser Disable Runner.
* Reach the required score to complete the challenge.

The collected evidence is necessary for the final stage of the game.

---

### Level 3 — Final Exposure

In the final level, the player faces the criminals and attempts to reach the police station.

**Main Challenges:**

* Fight the first guard to obtain a gun.
* Shoot the remaining enemy/criminal.
* Subway Surfer-style Traffic Runner.
* Avoid vehicles and reach the police station.

At the end, the player reaches the police station with the evidence and the truth is exposed.

**Ending:**
**Justice Deserved**

---

## Features

* Three progressive game levels.
* Multiple mini-games and challenges.
* Prison escape gameplay.
* Puzzle-based gameplay.
* CCTV and switch puzzle.
* Evidence collection system.
* USB collection mini-game.
* Vault / laser runner challenge.
* Guard combat.
* Shooting gameplay.
* Traffic Runner mini-game.
* Score and objective-based challenges.
* Multiple game states for different gameplay sections.
* Background music and sound integration.
* Menu system.
* Settings system.
* Pause system.
* Level unlocking system.
* Binary file-based Save/Load system.
* Automatic game progress saving.
* Different environments and background images.
* Final ending sequence at the police station.

---

## Project Details

**Project Name:** The Last Escape

**IDE:** Visual Studio 2013

**Language:** C, C++

**Graphics Library:** iGraphics

**Platform:** Windows PC

**Genre:** 2D Stealth / Puzzle / Action Adventure

**Project Type:** Graphics Programming Project

---

## Technologies Used

* **C/C++**
* **iGraphics Library**
* **Visual Studio 2013**
* **Binary File Handling**
* **Keyboard Input**
* **Mouse Input**
* **2D Graphics and Animation**
* **Game State Management**

---

## How to Run the Project

Make sure you have the following installed:

* **Visual Studio 2013**
* **iGraphics Library**
* Required project files included in this repository

### Steps

1. Clone or download this repository.
2. Open **Visual Studio 2013**.
3. Go to **File → Open → Project/Solution**.
4. Locate and open the project's `.sln` file.
5. Make sure the required iGraphics files and project dependencies are available.
6. Go to **Build → Build Solution**.
7. Run the program using **Debug → Start Without Debugging**.

---

## How to Play

### Controls

| Key / Input          | Action           |
| -------------------- | ---------------- |
| `←` Left Arrow       | Move Left        |
| `→` Right Arrow      | Move Right       |
| `↑` Up Arrow         | Jump             |
| `Space Bar`          | Jump             |
| `S`                  | Start Game       |
| `R`                  | Restart / Repeat |
| `Left Mouse Button`  | Shoot            |
| `Right Mouse Button` | Jump             |

The mouse is also used for interacting with menu buttons and certain game elements.

---

## Game Rules

* The player must complete the objectives of each level to progress.
* Completing the required puzzles unlocks the next stage.
* The player must avoid or overcome guards and enemies.
* Evidence must be collected before proceeding to the final stage.
* Certain mini-games require the player to achieve a specific score.
* The player must complete the final challenges and reach the police station.
* Progress can be saved using the binary Save/Load system.
* Completing the final stage leads to the ending sequence.

---

## Save & Load System

Thegame includes a binary file-based Save/Load system implemented using SaveSystem.h.

The system is used to preserve important game progress, such as:

Level progression.
Level unlocking status.
Completed game sections.
Other required gameplay states.

This allows the player to continue their progress without starting the entire game from the beginning.

Project Structure

The project is organized into separate header and source files to keep the game code structured.

Common Game System

Contains shared functionality such as:

Loading screen.
Main menu.
Settings.
Pause system.
Shared game variables.
Common game functions.
Level 1 Files

Contains Level 1 variables and game logic, including:

Prison map.
Cell escape.
Memory Puzzle.
Number Puzzle.
CCTV Switch Puzzle.
Falling Box.
Guard avoidance.
Level 2 Files

Contains Level 2 variables and game logic, including:

USB Hunt.
Evidence collection.
Room Number Puzzle.
Page Piece Puzzle.
Vault / Laser Runner.
Level 3 Files

Contains Level 3 variables and game logic, including:

Guard fight.
Gun collection.
Shooting section.
Traffic Runner.
Police station ending.
Save System

SaveSystem.h handles the binary Save/Load functionality used to preserve game progress.

Game Progression

The overall progression of the game is:

Captured → Prison Escape → CCTV Disabled → Investigation → Evidence Collection → Final Confrontation → Traffic Runner → Police Station → Justice Deserved

Each level must be completed before the next level becomes available.

Objective

The main objective of The Last Escape is to escape imprisonment, collect evidence against the criminals, survive the final confrontation, and reach the police station to expose the truth.

Escape. Investigate. Expose. Bring them to Justice.

Project Contributors
Member ID	Member Name	Member Contribution	Percentage Contribution
00725105101091	Sara Kabir Mridha	Traffic Runner, Binary File Save/Load System, SaveSystem.h	36%
—	Samrina Nowmin	Level 3 Shooting Section, Header File Development	33%
—	Muntah Mimu	Level 3 Fighting / Gun Collection, Music Integration, Image Updates, Game Code Modifications	34%
Screenshots
Menu

Add the game menu screenshot here.

Level 1 — BreakOut

<img width="600" height="400" alt="Screenshot (205)" src="https://github.com/user-attachments/assets/78ca1f15-58f8-451c-9b27-a49e54187f87" />




Level 2 — The Hidden File

<img width="1183" height="903" alt="Screenshot (194)" src="https://github.com/user-attachments/assets/2c5da11c-945f-4923-a10c-54ddff24b02a" />




Level 3 — Final Exposure


<img width="1195" height="897" alt="Screenshot (203)" src="https://github.com/user-attachments/assets/f45d6181-658a-4136-b9ba-9f481dc03786" />




Ending

<img width="1671" height="941" alt="temple5" src="https://github.com/user-attachments/assets/5c7f206e-6d8c-4d66-8ae1-a8ae2e2fd9b9" />



YouTube Link

The Last Escape — Gameplay / Project Video

Project Report

[Project Report.docx](https://github.com/user-attachments/files/32688222/Project.Report.docx)



Conclusion

The Last Escape combines different gameplay mechanics such as puzzles, stealth, combat, shooting, evidence collection, and runner-style challenges into one 2D game.

The project demonstrates the use of C/C++ programming, iGraphics, game states, keyboard and mouse input, animations, file handling, and modular game development to create a complete playable game.
