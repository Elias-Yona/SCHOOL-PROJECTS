-- Insert 10 records into the users table
INSERT INTO users (firstname, lastname, birthdate, address, phones)
VALUES
  ('John', 'Doe', '1980-01-01', ('123 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1212'), ('work', '555-555-1213')]),
  ('Jane', 'Doe', '1985-01-01', ('456 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1214'), ('work', '555-555-1215')]),
  ('Jim', 'Smith', '1990-01-01', ('789 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1216'), ('work', '555-555-1217')]),
  ('Jane', 'Smith', '1995-01-01', ('012 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1218'), ('work', '555-555-1219')]),
  ('Bob', 'Johnson', '2000-01-01', ('345 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1220'), ('work', '555-555-1221')]),
  ('Sarah', 'Johnson', '2005-01-01', ('678 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1222'), ('work', '555-555-1223')]),
  ('Tom', 'Williams', '2010-01-01', ('901 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1224'), ('work', '555-555-1225')]),
  ('Emily', 'Williams', '2015-01-01', ('234 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1226'), ('work', '555-555-1227')]),
  ('William', 'Brown', '2020-01-01', ('567 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1228'), ('work', '555-555-1229')]),
  ('Emma', 'Brown', '2025-01-01', ('890 Main St', 'Anytown', 'Anystate', '12345'),
   [('home', '555-555-1230'), ('work', '555-555-1231')]);


-- Insert 10 records into the books table
INSERT INTO books (info)
VALUES
  ('The Great Gatsby', ARRAY[('F. Scott', 'Fitzgerald')], ('Charles Scribner''s Sons', '1925-04-10', '9780743273565')),
  ('To Kill a Mockingbird', ARRAY[('Harper', 'Lee')], ('J. B. Lippincott & Co.', '1960-07-11', '9780446310789')),
  ('The Catcher in the Rye', ARRAY[('J.D.', 'Salinger')], ('Little, Brown and Company', '1951-07-16', '9780316769488')),
  ('1984', ARRAY[('George', 'Orwell')], ('Secker and Warburg', '1949-06-08', '9780547249643')),
  ('Pride and Prejudice', ARRAY[('Jane', 'Austen')], ('T. Egerton, Whitehall', '1813-01-28', '9780199540373')),
  ('Moby-Dick; or, The Whale', ARRAY[('Herman', 'Melville')], ('Richard Bentley', '1851-10-18', '9780679783268')),
  ('The Adventures of Huckleberry Finn', ARRAY[('Mark', 'Twain')], ('Chatto & Windus', '1884-12-10', '9780141395364')),
  ('Wuthering Heights', ARRAY[('Emily', 'Bronte')], ('Thomas Cautley Newby', '1847-12-17', '9780141439556')),
  ('The Picture of Dorian Gray', ARRAY[('Oscar', 'Wilde')], ('Ward, Lock & Co.', '1890-06-20', '9780141391229')),
  ('The Lord of the Rings', ARRAY[('J.R.R.', 'Tolkien')], ('George Allen & Unwin', '1954-07-29', '9780544003415'));


-- Insert 10 records into the loans table
INSERT INTO loans (bookid, userid, loan_date, due_date)
VALUES
  (1, 1, '2023-01-01', '2023-01-08'),
  (2, 2, '2023-01-02', '2023-01-09'),
  (3, 3, '2023-01-03', '2023-01-10'),
  (4, 4, '2023-01-04', '2023-01-11'),
  (5, 5, '2023-01-05', '2023-01-12'),
  (6, 6, '2023-01-06', '2023-01-13'),
  (7, 7, '2023-01-07', '2023-01-14'),
  (8, 8, '2023-01-08', '2023-01-15'),
  (9, 9, '2023-01-09', '2023-01-16'),
  (10, 10, '2023-01-10', '2023-01-17');