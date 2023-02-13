CREATE DATABASE library;

CREATE TYPE address AS (
  street text,
  city text,
  state text,
  zipcode text
);

CREATE TYPE phone AS (
  type text,
  number text
);

CREATE TYPE publication_info AS (
  publisher text,
  publication_date date,
  ISBN text
);

CREATE TYPE author AS (
  first_name text,
  last_name text
);

CREATE TYPE book_info AS (
  title text,
  authors author[],
  publication_info publication_info
);

CREATE TABLE users (
  userid serial PRIMARY KEY,
  firstname text NOT NULL,
  lastname text NOT NULL,
  birthdate date NOT NULL,
  address address NOT NULL,
  phones phone[]
);

CREATE TABLE books (
  bookid serial PRIMARY KEY,
  info book_info NOT NULL
);

CREATE TABLE loans (
  loanid serial PRIMARY KEY,
  bookid integer REFERENCES books (bookid),
  userid integer REFERENCES users (userid),
  loan_date date NOT NULL,
  due_date date NOT NULL
);
