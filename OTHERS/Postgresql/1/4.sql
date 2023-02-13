-- This query retrieves the first name, last name, birth date, address, and phone information of all users.
SELECT firstname, lastname, birthdate, address, phones FROM users;

-- This query retrieves the book id, title, authors, and publication information of all books.
SELECT bookid, title, authors, publication_info FROM books;

-- This query retrieves the loan id, book id, user id, loan date, and due date of all loans.
SELECT loanid, bookid, userid, loan_date, due_date FROM loans;

-- This query retrieves the title, authors, and publication information of all books that contain the word "history" in their title.
SELECT title, authors, publication_info
FROM books
WHERE title LIKE '%history%';

-- This query retrieves the first name, last name, loan id, book id, and loan date of all loans made by users.
SELECT firstname, lastname, loanid, bookid, loan_date
FROM users
JOIN loans ON users.userid = loans.userid;
