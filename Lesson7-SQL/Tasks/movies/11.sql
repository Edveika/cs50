SELECT m.title, r.rating
FROM movies AS m
JOIN people AS p ON p.name = "Chadwick Boseman"
JOIN stars AS s ON s.person_id = p.id
JOIN ratings AS r ON r.movie_id = s.movie_id
WHERE s.movie_id = m.id
ORDER BY r.rating DESC
LIMIT 5;