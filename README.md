# CSC 310 Final Project

Our process:
* Read employee records from txt file into separate linked lists for each department
* Sort each linked list by employee ID
* Write all records to binary file
   * Order by department
   * Order by employee ID within each department
   * Create index array while writing binary for better search performance
* Test functionality by reading employee records from test records file
* Search for test records in binary file
   * If found, print employee details and change employee name

Beginning of **data/smallOutput.txt** employee records input txt file (*department number, employee number, employee name*):

```
1,0,Emma
1,1,Olivia
1,2,Ava
2,3,Isabella
4,4,Sophia
1,5,Charlotte
0,6,Mia
2,7,Amelia
...
```

Sample execution using **data/SmallOutput.txt** as input file and searching for employee records in **data/smallOutput_TestRecords.txt**, which includes 5 valid records and 5 records not found in input file:

```
./excBinaryFile
Employee found
*******EMPLOYEE DETAILS*******
	Department: ACCOUNTING
	Employee Number: 45731
	Employee Name: Leona
Employee updated
------------------------------
Employee found
*******EMPLOYEE DETAILS*******
	Department: BUSINESS
	Employee Number: 37503
	Employee Name: Briar
Employee updated
------------------------------
Employee found
*******EMPLOYEE DETAILS*******
	Department: HUMAN RESOURCES
	Employee Number: 58509
	Employee Name: Kailey
Employee updated
------------------------------
Employee found
*******EMPLOYEE DETAILS*******
	Department: SALES
	Employee Number: 58510
	Employee Name: Liv
Employee updated
------------------------------
Employee found
*******EMPLOYEE DETAILS*******
	Department: PRODUCTION
	Employee Number: 44258
	Employee Name: Anthony
Employee updated
------------------------------
Employee not found
------------------------------
Employee not found
------------------------------
Employee not found
------------------------------
Employee not found
------------------------------
Employee not found
------------------------------
```

---

### Instructions
Provided data files: smallOutput.txt, mediumOutput.txt, and largeOutput.txt. Each file is comprised of records representing an employee of a fictitious company, and follows these rules:
* Each line represents the record of one employee. 
* Each record is comprised of department number, employee number, and employee name. 
* There are 5 possible departments: Accounting(0), Business(1), Human Resources(2), Sales(3), and Production(4). 
* The maximum allowable employee name is 30 characters.

You will create a C++ class called ‘binaryFile’ that will implement methods that are described below. You must use a header file for the class which will contain the class definition, all structure and/or enumerator definitions, and header files necessary for execution.
*	Read data from a file (described in the “Details” section above) and writes the data out to a binary file. (5 pts)
*	Sort the binary file by department, and within each department sort in ascending order (0…100) by employee number. (10 pts)
*	Search the binary file for an employee based on the department and employee number. The public method must return a bool (true/false) that represents if the employee was found or not. The public method must only take the department number and employee number as arguments. The private method should return the offset within the file where the employee is located. (10 pts)
    *	In main, use the return value to print “Employee found” or “Employee not found”. This should not be part of the ‘search’ method’s functionality.
*	Retrieve from the binary file an employee based on the department and employee number. This public method must return the employee details (department, employee number, and name.)  The public method must only take the department number and employee number as arguments. (10 pts)
    * In main, use the return value to print the employee details to the screen. This should not be part of the ‘retrieve’ method’s functionality.
*	Update an employee’s name based on the department and employee number. The public method must return a bool (true/false) that represents if the employee was updated or not. The public method must only take a structure containing the employee’s department, number, and string. (10 pts)
*	In main, use the return value to print “Employee updated” or “Employee not updated”. This should not be part of the ‘search’ method’s functionality.
*	Use the provided exception handling class to create exceptions as appropriate to account for, at a minimum: inability to open files, data does not conform to expectations, error occurred during normal operations. Examples situations that should result in an exception handling message. (10 pts)
    *	File does not exist
    *	Employee name exceeds 30 characters
    *	Could not convert employee record from text to binary.

Your class will follow the principle of accessing private variables from the private scope and using getters and setters to retrieve and store or update public and private variables. 

You will also utilize a Makefile which will at a minimum do the following (5 pts):
*	Create the executable binary “excBinaryFile”.
*	Create a clean rule which will remove all files created from the build and execution processes to include \*.o files, excBinaryFile, and any temporary files that may have been created during the execution of excBinaryFile.
*	Create object files for linking into the excBinaryFile.
