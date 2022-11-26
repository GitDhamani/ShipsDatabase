# ShipsDatabase
Data Management System for a Ship Database, written in C++, QT and SQL.

A Data Management System to organise information related to Aircraft Carriers, Destroyers and Frigates.
You can update existing records as well as add new ones. You can also delete records.
There is a filter field at the bottom, so you can pull up only the Ship types you are interested in.

The program works by initially including the SQL Modules into the QT Framework Library.
The Database was first created in Excel and exported as a Comma Separated Value (.CSV) File.
It was then imported into SQLite to create the actual light-weight database.

In QT, the initial step involves loading the correct Driver for SQLite and then assigning our database file
to our Database itself. We then construct an initial query to display the entire contents of our Database to a Query Model which is then
loaded into the List View.

The Add, Update, Delete and Clear Buttons are all coded to read the information in the edit fields and use them to
perform those operations. Clicking on the name fields in the List View causes that record to populate the edit fields for later updates or deletion.

Finally, the filter edit field at the bottom allows only field with a matching Class Type to be displayed and it does this
by using the SQL Select Syntax.

https://user-images.githubusercontent.com/111576658/204095527-e3d5df7f-11d8-4045-920d-6354232cfbbd.mp4

