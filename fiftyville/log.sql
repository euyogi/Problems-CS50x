-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Take a look into all tables of the database
.sch

-- Check what this table has to start to understand the database
SELECT * FROM crime_scene_reports LIMIT 10;
-- Looks like there's a description of each crime, let's see if it has more info than the ones we have

-- Get more info about the crime that I'm investigating
SELECT id, description FROM crime_scene_reports
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND street = "Humphrey Street";
-- The crime happened at 10:15 am on a bakery
-- There was three witnesses who gave interviews, and everyone mentioned the bakery

-- Let's read the interviews of those witnesses
SELECT name, transcript FROM interviews
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND transcript LIKE "%bakery%";
-- Eugene saw the thief withdrawing money on an ATM at Leggett Street on the same day the crime happened
-- Ruth saw that within ten minutes of the theft, the thief got in a car in the bakery parking lot and drove away
-- Raymond saw the thief calling someone for less than a minute to buy him the earliest flight out of Fiftyville for the day after the crime happened

-- Let's start looking at the ATM transactions that Eugene told
SELECT account_number, transaction_type, amount FROM atm_transactions
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = "Leggett Street";
-- So we have a list of account_numbers which one of those is the one of the thief, except the one that deposited
-- I'LL CALL THIS WITH ONLY THE ACCOUNT NUMBER LIST 0

-- But as people table doesn't have an account number column, I'm gonna get a list with the ids of those accounts
SELECT person_id FROM bank_accounts
    WHERE account_number IN
        -- LIST 0
        (SELECT account_number FROM atm_transactions
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND atm_location = "Leggett Street"
            AND transaction_type = "withdraw");
-- I'LL CALL THIS LIST 1

-- Ok, now let's see the security logs of the bakery to get more info about the car in which the thief drove away
SELECT hour, minute, activity, license_plate FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    -- As the crime happened at 10>15 and Ruth said that the thief drove away within ten minutes of the theft
    AND minute > 15
    AND minute <= 25;
-- I'LL CALL THIS WITH ONLY THE LICENSES PLATE LIST 2

-- Now let's see the duration column on phone calls table just so I can see if the duration is in seconds or what
SELECT duration FROM phone_calls
    LIMIT 10;
-- Of course, seconds who talks for 469 minutes on a phone call?

-- Let's see the phone_calls on the crime day that lasted less than one minute as Raymond described
SELECT caller, receiver FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60;
-- Ok a list of numbers in which there are the numbers of the thief and the accomplice
-- I'LL CALL THIS WITH ONLLY THE CALLER NUMBER LIST 3

-- What if I try to get the earliest flight out of Fiftyville on the day after the crime happened
SELECT id, hour, minute FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    AND origin_airport_id IN (
        SELECT id FROM airports
            WHERE city = "Fiftyville"
    )
    ORDER BY hour, minute;
-- The earliest flight out of Fiftyville on the day after the crime happened has 36 as it's id

-- Let's get a list with the passengers passport numbers on that flight
SELECT passport_number FROM passengers
    WHERE flight_id = 36;
-- I'LL CALL THIS LIST 4

-- Ok, finally I have all info needed as the thief id, license plate, phone number and passport number in LIST 1, LIST2, LIST 3 and LIST 4 respectively

-- Let's get his naaame :) and his phone number so that we can find accomplice name
SELECT name, phone_number FROM people
    WHERE id IN
        -- LIST 1
        (SELECT person_id FROM bank_accounts
            WHERE account_number IN
                (SELECT account_number FROM atm_transactions
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND atm_location = "Leggett Street"
                    AND transaction_type = "withdraw"))
    AND license_plate IN
        -- LIST 2
        (SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute > 15
            AND minute <= 25)
    AND phone_number IN
        -- LIST 3
        (SELECT caller FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60)
    AND passport_number IN
        -- LIST 4
        (SELECT passport_number FROM passengers
            WHERE flight_id = 36);
-- Bruce, (367) 555-5533

-- Now let's see who Bruce called
SELECT receiver FROM phone_calls
    WHERE "(367) 555-5533" = caller
    AND year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60;

-- And get his name
SELECT name FROM people
    WHERE phone_number = "(375) 555-8161";
-- Robin

-- Almost forgot, but what city did Bruce escaped to?
SELECT city FROM airports
    WHERE id =
        (SELECT destination_airport_id FROM flights
            WHERE id = 36);
-- New York City

-- The End