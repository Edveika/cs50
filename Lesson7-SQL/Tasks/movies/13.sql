-- 1. Surast Kevin id
-- 2. Surast Kevin movie id lista
-- 3. Jei stars movie id sutampa su kevino, selectint name

SELECT DISTINCT p.name 
FROM people as p
JOIN stars as s ON s.person_id = p.id
WHERE s.movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958));