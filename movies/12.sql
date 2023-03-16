SELECT title FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = "Helena Bonham Carter"
    AND title IN (
        SELECT title FROM movies
            JOIN stars ON movies.id = stars.movie_id
            JOIN people ON stars.person_id = people.id
            WHERE people.name = "Johnny Depp"
    );
