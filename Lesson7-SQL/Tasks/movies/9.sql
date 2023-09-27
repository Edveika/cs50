-- SQL query to list the names of all 
-- people who starred in a movie released in 2004,
-- ordered by birth year. 

SELECT p.name, p.birth
FROM people AS p
JOIN directors AS d ON p.id = d.person_id
JOIN movies AS m ON m.id = d.movie_id
WHERE m.year = 2004
ORDER BY p.birth;