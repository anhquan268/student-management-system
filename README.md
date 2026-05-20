# Student Management System

A comprehensive console-based C++ application for managing student information, academic records, placement activities, and library resources in an educational institution.

---

## Features

### 1. Student Information Section

**Admission Details Module**
- Register new students with personal information
- Display all student records
- Search students by roll number
- Delete student records

**Grading System Module**
- Upload student grades (out of 500 marks)
- Automatic percentage and grade calculation (A+ to F)
- View all grades
- Search grades by roll number
- Delete grade records

**Placement Cell Module**
- Add student profiles (name, roll number, CGPA)
- Add company information (name, package, minimum CGPA requirement)
- Find eligible students based on company criteria
- Track placement opportunities

### 2. Library Management System

- **Category-based organization**: Computer Science, Electronics, Electrical, Mechanical, Civil, First Year
- **Book management**: Add, view, search, and remove books
- **Inventory tracking**: Track book quantities
- **Issue/Return system**: Manage book circulation
- **Role-based access**: Different options for students and staff

---

## Project Structure

```
StudentManagementSystem/
├── StudentManagementSystem.cpp   # Main source file (all modules)
├── header.h                     # Cross-platform utilities
├── README.md                    # This file
├── Data Files (generated at runtime):
│   ├── student.txt              # Binary student records
│   ├── grade.txt                # Binary grade records
│   ├── studentList.txt          # Placement student data
│   ├── companyList.txt          # Placement company data
│   ├── csBooks.txt              # Computer Science books
│   ├── eceBooks.txt             # Electronics books
│   ├── elecBooks.txt            # Electrical books
│   ├── mechBooks.txt            # Mechanical books
│   ├── civilBooks.txt           # Civil books
│   └── yearOneBooks.txt         # First Year books
```

---

## Getting Started

### Prerequisites

- **C++ Compiler**: GCC (MinGW on Windows), Clang, or MSVC
- **Operating System**: Windows or Linux/Unix

### Compilation

**Windows (using MinGW):**

```bash
g++ StudentManagementSystem.cpp -o StudentManagementSystem.exe
```

**Windows (using MSVC):**

```bash
cl StudentManagementSystem.cpp
```

**Linux/Unix:**

```bash
g++ StudentManagementSystem.cpp -o StudentManagementSystem
```

### Running the Application

**Windows:**

```bash
StudentManagementSystem.exe
```

**Linux/Unix:**

```bash
./StudentManagementSystem
```

---

## User Guide

### Main Menu

```
**************************************************
            STUDENT MANAGEMENT SYSTEM
**************************************************
    1. STUDENT INFORMATION SECTION
    2. LIBRARY MANAGEMENT SYSTEM
    0. Exit.

Enter your choice :
```

### Student Information Section

```
**************************************************
            STUDENT INFORMATION SECTION
**************************************************
    1. STUDENT INFORMATION SECTION
    2. LIBRARY MANAGEMENT SYSTEM
    0. Exit.

Enter your choice : 1
```

#### Admission Details Sub-menu

```
**************************************************
            STUDENT INFORMATION SECTION
**************************************************
                 ADMISSION DETAILS
--------------------------------------------------
    1.  Register Student
    2.  Display all Records.
    3.  Search for a Record
    4.  Delete a Record.
    0.  Exit.
```

#### Grading System Sub-menu

```
**************************************************
            STUDENT INFORMATION SECTION
**************************************************
                 GRADING SYSTEM
--------------------------------------------------
    1.  Upload Grades
    2.  View All Grades
    3.  Search Grades By Roll Number
    4.  Delete a Grade Record
    0.  Exit.
```

#### Placement Cell Sub-menu

```
**************************************************
            STUDENT INFORMATION SECTION
**************************************************
                 PLACEMENT CELL
--------------------------------------------------
    1. Add Student
    2. Add Company
    3. Show Eligible students
    4. Back
```

### Library Management System

```
**************************************************
                LIBRARY DETAILS
**************************************************
    >> Choose any option

    1. Student
    2. Staff
    0. Back To Main
```

---

## Technical Details

### Cross-Platform Support

The application automatically detects the operating system and uses appropriate functions:
- **Windows**: `system("cls")` for clearing screen, Win32 API for cursor positioning
- **Unix/Linux**: ANSI escape sequences for terminal manipulation

### Data Storage

| Data Type | Storage Method | File Format |
|-----------|---------------|-------------|
| Student Records | Binary | `student.txt` |
| Grade Records | Binary | `grade.txt` |
| Placement Data | Text | `studentList.txt`, `companyList.txt` |
| Library Books | Text | Category-specific files |

### Key C++ Features Used

- Object-Oriented Programming (classes, encapsulation)
- File I/O (binary and text modes)
- Stream handling (`iostream`, `fstream`)
- Preprocessor directives for cross-platform compatibility
- Function overloading and operator overloading

---

## Input Validation

The system includes robust input validation:
- **Integer inputs**: Rejects non-numeric values
- **Roll numbers**: Must be positive integers
- **CGPA**: Must be between 0.0 and 10.0
- **String inputs**: Cannot be empty
- **Menu choices**: Must be within valid range

---

## Sample Data

### Student Record Format

```
Student Name  : Mr John Doe
Roll No.      : 101
Father's Name : Robert Doe
Mother's Name : Jane Doe
Address       : 123 Main Street
Blood Group   : O+
```

### Grade Record Format

```
Student Name     : John Doe
Roll No.         : 101
Total            : 425
Percentage       : 85.00
Grade: A
```

---

## Known Limitations

- No database integration (flat file storage)
- No password/authentication system
- Sequential search (no indexing)
- No modification/update of existing records
- Code duplication across similar functions
- Uses legacy C-style string handling

---

## Future Improvements

- [ ] Add database support (SQLite/MySQL)
- [ ] Implement user authentication
- [ ] Add record modification capability
- [ ] Implement search by multiple fields
- [ ] Add sorting functionality
- [ ] Export reports to PDF/CSV
- [ ] GUI interface
- [ ] Network/database server mode

---

## Credits

This project was developed as a collaborative academic project:

| Module | Contributor |
|--------|-------------|
| Student Management & Grading | Main Developer |
| Placement Cell | Dibya & Amlan |
| Library Management | Team Project |

---

## License

This project is created for educational purposes.

---

## Contact

For questions or suggestions, please refer to the code documentation in `CodeExplanation.md`.
