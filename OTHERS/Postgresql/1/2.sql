-- A function that calculates the due date based on the loan date and number of loan days
CREATE OR REPLACE FUNCTION calculate_due_date(loan_date date, loan_days integer)
RETURNS date AS $$
BEGIN
  RETURN loan_date + loan_days;
END; $$
LANGUAGE plpgsql;

-- A function that calculates the number of books checked out by a user
CREATE OR REPLACE FUNCTION number_of_books_checked_out(userid integer)
RETURNS integer AS $$
DECLARE
  result integer;
BEGIN
  SELECT COUNT(*) INTO result
  FROM loans
  WHERE userid = userid;

  RETURN result;
END; $$
LANGUAGE plpgsql;

-- A procedure that returns a loaned book
CREATE OR REPLACE PROCEDURE return_book(loanid integer)
LANGUAGE plpgsql AS $$
BEGIN
  DELETE FROM loans
  WHERE loanid = loanid;
END; $$

-- A trigger that enforces a maximum of 5 books that can be checked out by a user
CREATE OR REPLACE TRIGGER check_loan_limit
BEFORE INSERT ON loans
FOR EACH ROW
BEGIN
  IF number_of_books_checked_out(NEW.userid) >= 5 THEN
    RAISE EXCEPTION 'A user cannot have more than 5 books checked out.';
  END IF;
END;