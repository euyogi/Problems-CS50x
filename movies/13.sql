SELECT name FROM people
    WHERE people.id IN (
        SELECT people.id FROM people
            JOIN stars ON people.id = stars.person_id
            JOIN movies ON stars.movie_id = movies.id
            WHERE movies.title IN (
                SELECT title FROM movies
                    JOIN stars ON movies.id = stars.movie_id
                    JOIN people ON stars.person_id = people.id
                    WHERE people.name = "Kevin Bacon" AND people.birth = "1958"
            )
            AND people.id != (
                SELECT people.id FROM people
                    WHERE people.name = "Kevin Bacon" AND people.birth = "1958"
            )
    );
