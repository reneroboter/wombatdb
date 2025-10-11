# Renés Simple SQL Interpreter (incl. CSV database)

## Preface 

I want to build my own, very, very simple SQL interpreter, which can also interact with a tiny, tiny database management system. The actual main goal is to write my own interpreter. That's why the focus is rather on tokenizer, parser, AST and executing the AST. Therefore I will not follow a server/client concept. Very straight forward project with chichi (expecting maybe CSV database engine)
 
## How does the database concept looks like?

- The database management system will only support one database 
- The database is a folder called `database`
- The database can contain `n` tables 
- Each table is a CSV file
- Each query will require a `full table scan` 🤷‍♂️


## Which statements should be supported?

### SELECT clause
```sql
SELECT column1, column2, ...
FROM table_name;
```
### WHERE clause
```sql
SELECT column1, column2, ...
FROM table_name
WHERE condition;
```
**NOTE:** No support plannend for `AND`, `OR`, `NOT` or `LIKE` etc. 

### ORDER BY clause
```sql
SELECT column1, column2, ...
FROM table_name
ORDER BY column1, column2, ... ASC|DESC;
```


### LIMIT clause
```sql
SELECT column1, column2, ...
FROM table_name
LIMIT limit OFFSET offset
```

### INSERT clause
```sql
INSERT INTO table_name (column1, column2, column3, ...)
VALUES (value1, value2, value3, ...);
```
### CREATE TABLE clause

```sql
CREATE TABLE table_name (
    column1,
    column2,
    column3,
   ....
);
```
**NOTE:** No support plannend for datatypes. 

## Getting started

1. `gcc interpreter.c tokenizer.c -o main` or `make main`
2. `./main`

### How to execute tests?
1. `brew install cunit` 
1. `gcc -o tests tests.c -I/opt/homebrew/Cellar/cunit/2.1-3/include -L/opt/homebrew/Cellar/cunit/2.1-3/lib -lcunit` or `make tests`
1. `./tests`

## ToDos

- Add str_to_lower in is_keyword function for comparsion
- Use termination char to end while loop
- Add a least one test for each SQL clause
- Add praser to validate correctness of tokens and create AST from them
- Execute AST
- Add simple datbase as explained above 