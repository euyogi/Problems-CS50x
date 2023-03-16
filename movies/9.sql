SELECT DISTINCT(name) FROM people
    JOIN stars ON people.id = person_id
    JOIN movies ON movies.id = movie_id
    WHERE year = "2004"
    ORDER BY birth;