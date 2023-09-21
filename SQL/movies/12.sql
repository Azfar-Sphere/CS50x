SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars where movie_id IN
(SELECT movie_id FROM stars where person_id IN
(SELECT id FROM people WHERE name = 'Bradley Cooper'))
AND person_id IN (SELECT id FROM people WHERE name = 'Jennifer Lawrence'))
;