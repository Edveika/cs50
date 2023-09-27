SELECT m.title
FROM movies AS m
JOIN stars AS s1 ON m.id = s1.movie_id
JOIN stars AS s2 ON m.id = s2.movie_id
JOIN people AS p1 ON p1.id = s1.person_id AND p1.name = "Bradley Cooper"
JOIN people AS p2 ON p2.id = s2.person_id AND p2.name = "Jennifer Lawrence"
WHERE s1.movie_id = s2.movie_id;