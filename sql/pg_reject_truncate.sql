CREATE EXTENSION pg_reject_truncate;
LOAD 'pg_reject_truncate';

---
--- set up a table
---
CREATE TABLE pg_reject_truncate_test (
	id INTEGER
);
INSERT INTO pg_reject_truncate_test VALUES(1);

--- check the contents of the table
SELECT * FROM pg_reject_truncate_test;

--- truncate
TRUNCATE pg_reject_truncate_test;

--- check table still exists and  recheck the contents of the table
SELECT * FROM pg_reject_truncate_test;

DROP EXTENSION pg_reject_truncate;
