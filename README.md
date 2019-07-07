# Actian_Pervasive_SQL README

The __Actian_Pervasive_SQL__ repository is a collection of Visual Studio solutions, each of
which is a complete console program that demonstrates a basic __ACID__ (Add/Change/Inquire/Delete)
application, also known as a __CRUD__ (Create/Read/Update/Delete) application.

To the extent possible, the code is portable C++, except for `PSQLviaADOandVB`,
which is implemented in Visual Basic .NET. The Visual Basic code is sufficiently
portable that it could be transformed with little effort into a working Visual
Basic for Applications module.

All solutions were built by Visual Studio 2017 Community Edition, and tested on
a machine running Windows 10 Professional with a working PSQL Server installation.
The Visual Basic application and its C++ companion use the demonstration database
that ships with the PSQL Server, along with its System DSN, which the PSQL Server
setup program creates.