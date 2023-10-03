-- Keep a log of any SQL queries you execute as you solve the mystery.

-- [KNOWN INFO]
-- Theft took place on July 28, 2021
-- It took place on Humphrey Street
-- Stolen: duck
-- Theft of the CS50 duck took place at 10:15am

-- [TO FIND]
-- Who the thief is,
-- What city the thief escaped to, and
-- Who the thief’s accomplice is who helped them escape


-- Get crime scene report of date when the duck was stolen
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street LIKE "%Humphrey%";

-- Get interviews that mention bakery
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 transcript LIKE "%bakery%";

-- [THIEF WAS HERE]License plates of cars that left the bakery aprox 10 minutes after theft
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND minute > 15 AND minute <= 25;

--
-- Money stuff
--

-- [THIEF WAS HERE] atm cash withdrawal
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- [THIEF IS HERE] id of people who got cash
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");

--
-- Phone calls
--

-- [THIEF IS HERE] phone calls that lasted less than 1 minute on the day of the robbery
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

--
-- Flights
--

-- Fiftyville airport ID(8)
SELECT id FROM airports WHERE city = "Fiftyville";

-- Earliest flight next day
SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute DESC LIMIT 1;

-- Passport from flight
SELECT passport_number FROM passengers WHERE flight_id = 36;

-- suspects
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND minute > 15 AND minute <= 25);

-- Cross reference suspects to people who took cash from atm(686048)
SELECT person_id FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND activity = "exit" AND hour = 10 AND minute > 15 AND minute <= 25));

-- Suspect: Bruce
SELECT name FROM people WHERE id = 686048;

-- Bruces phone number(555-5533)
SELECT phone_number FROM people WHERE id = 686048;

-- Find helper(person who thief called)
SELECT receiver FROM phone_calls WHERE caller LIKE "%555-5533%" AND year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- find his name(Robin)
SELECT name FROM people WHERE phone_number LIKE "%555-8161%";

-- Bruces passport(5773159633)
SELECT passport_number FROM people WHERE id = 686048;

-- Bruces flight id
SELECT flight_id FROM passengers WHERE passport_number = 5773159633;

-- Destination air port(4)
SELECT destination_airport_id FROM flights WHERE id = 36;

-- City where thief is headed(NYC)
SELECT city FROM airports WHERE id = 4;