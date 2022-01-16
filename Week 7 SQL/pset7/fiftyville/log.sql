-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1-
-- We conducted that:
-- There was 3 witnesses who mentioned the "courthouse" in their interviews.
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";


/*
Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/
-- 2-
-- We conducted that:
-- The theif drive away a car within ten minutes of the theft which happened at 10:15am.
-- He was withdrawing some money ftom ATM in Fifer Street Before 10:15am.
-- He called someone less than 60 secs
-- He Wil take the earliest flight out of Fiftyville at 29/7/2020.
SELECT name, transcript FROM "interviews" WHERE "year" = '2020' AND "month" = '7' AND "day" = '28' AND "transcript" LIKE '%courthouse%';

-- 3-
-- We conducted that:
-- There are 8 suspicious cars that left the parking lot within ten minutes of the theft.
SELECT license_plate FROM "courthouse_security_logs" WHERE "year" = '2020' AND "month" = '7' AND "day" = '28' AND "hour" = '10' AND "minute" BETWEEN '15' AND '25' AND "activity" LIKE 'exit';

-- 4-
-- We conducted that:
-- There are 8 suspicious people that was withdrawing money from fifer st. at 28/7/2020.
SELECT account_number FROM "atm_transactions" WHERE "year" = '2020' AND "month" = '7' AND "day" = '28' AND "atm_location" LIKE '%fifer%' AND "transaction_type" LIKE '%withdraw%';

-- 5-
-- We conducted that:
-- The Theif will go to london ########
-- SELECT id FROM "airports" WHERE "city" LIKE 'Fiftyville';
-- SELECT destination_airport_id FROM "flights" WHERE "origin_airport_id" = '8' AND "year" = '2020' AND "month" = '7' AND "day" = '29' ORDER BY hour LIMIT 1;
SELECT city FROM "airports" WHERE id IN (SELECT destination_airport_id FROM "flights" WHERE "origin_airport_id" IN (SELECT id FROM "airports" WHERE "city" LIKE 'Fiftyville') AND "year" = '2020' AND "month" = '7' AND "day" = '29' ORDER BY hour LIMIT 1);

-- 6-
-- We conducted that:
-- There are 10 suspicious people who made calls after the theft immediately for about 1 Sec.
SELECT caller, receiver FROM "phone_calls" WHERE "year" = '2020' AND "month" = '7' AND "day" = '28' AND "duration" <= '60'

-- 7- Collecting 4 & 6
-- We conducted that:
-- There are 4 suspicious people.
SELECT name, phone_number, passport_number FROM people WHERE phone_number IN (
SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60
INTERSECT
SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND activity = "exit")
);

-- 8- Collecting all
-- We conducted that:
-- There are 2 suspicious people.
SELECT name FROM people WHERE id IN (
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw")
)
INTERSECT
SELECT name FROM people WHERE passport_number IN (
SELECT passport_number FROM people WHERE phone_number IN (
SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60
INTERSECT
SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND activity = "exit")
)
);

-- 9-
-- We conducted that:
-- The id of the flight from Fiftyvilla to London at 29/7/2020
SELECT id FROM "flights" WHERE "origin_airport_id" = '8' AND "destination_airport_id" = '4' AND "month" = '7' AND "day" = '29'


--10- Final
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
INTERSECT
SELECT name FROM people WHERE passport_number IN (
SELECT passport_number FROM people WHERE phone_number IN (
SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60
INTERSECT
SELECT phone_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute < 25 AND activity = "exit")
)
INTERSECT
SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM "flights" WHERE "origin_airport_id" = '8' AND "destination_airport_id" = '4' AND "month" = '7' AND "day" = '29')
);

-- Getting the name
SELECT name FROM people WHERE phone_number IN (
SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name = "Ernest") AND year = 2020 AND month = 7 AND day = 28 AND duration < 60);
