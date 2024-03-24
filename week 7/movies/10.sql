SELECT DISTINCT people.name
FROM directors
JOIN people ON directors.person_id = people.id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON ratings.movie_id = movies.id
WHERE rating >=9;
