-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To get the description of the incident
SELECT description
    FROM crime_scene_reports
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND street = 'Humphrey Street';

-- To look into the case we need the transcripts of the witnesses
SELECT name, transcripts
    FROM interviews
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND transcript LIKE '%bakery%';

-- WITNESS 1 - Ruth
-- To check bakery security logs
SELECT minute, license_plate
    FROM bakery_security_logs
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND hour = 10
        AND activity = 'exit'
        AND minute BETWEEN 15 AND 25;

-- Names of people against the license plate
SELECT name, phone_number, minute, bakery_security_logs.license_plate
    FROM bakery_security_logs
        INNER JOIN people ON people.license_plate = bakery_security_logs.license_plate
        WHERE year= 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND activity = 'exit'
            AND minute BETWEEN 15 AND 25;

-- WITNESS 2 - Eugene
-- To check atm details
SELECT account_number, amount
    FROM atm_transactions
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND transaction_type = 'withdraw'
        AND atm_location = 'Leggett Street';

-- To extract name against the account_number
SELECT bank.account_number, people.name
    FROM atm_transactions atm
        INNER JOIN bank_accounts bank ON atm.account_number = bank.account_number
        INNER JOIN people ON people.id = bank.person_id
        WHERE year = 2023
            AND day = 28
            AND month = 7
            AND transaction_type = 'withdraw'
            AND atm_location = 'Leggett Street';


-- WITNESS 3 - Raymond
-- To check the call details
SELECT caller, receiver, duration
    FROM phone_calls
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND duration < 60;

-- To extract names against the phone number
SELECT caller.name AS caller_name, phone_calls.caller, receiver.name AS receiver_name, phone_calls.receiver
    FROM phone_calls
    JOIN people caller ON phone_calls.caller = caller.phone_number
    JOIN people receiver ON phone_calls.receiver = receiver.phone_number
    WHERE year = 2023
        AND month = 7
        AND duration < 60
        AND day = 28;

-- Explore airport to find fifty ville
SELECT *
    FROM airports;

-- Explore flights of fiftyville (id: 8)
SELECT flights.id, flights.hour, flights.minute, origin.full_name AS origin_airport, destination.full_name AS destination_airport
    FROM flights
    JOIN airports origin ON flights.origin_airport_id = origin.id
    JOIN airports destination ON flights.destination_airport_id = destination.id
    WHERE origin.id = 8
        AND flights.year = 2023
        AND flights.month = 7
        AND flights.day = 29
        ORDER BY flights.hour, flights.minute;


-- Catching the culprit
SELECT people.name
FROM people
JOIN passenger ON passenger.passport_number = people.passport_number
WHERE passenger.flight_id = 36
AND people.name IN (
    SELECT DISTINCT people.name
    FROM bakery_security_logs bsl
    JOIN people ON people.license_plate = bsl.license_plate
    JOIN bank_accounts bank ON bank.person_id = people.id
    JOIN atm_transactions atm ON atm.account_number = bank.account_number
    JOIN phone_calls calls ON calls.caller = people.phone_number
    WHERE bsl.year = 2023
        AND bsl.month = 7
        AND bsl.day = 28
        AND bsl.hour = 10
        AND bsl.minute BETWEEN 15 AND 25
        AND atm.atm_location = 'Leggett Street'
        AND atm.transaction_type = 'withdraw'
        AND calls.duration < 60;
);

-- Accomplice of Bruce
SELECT receiver.name AS receiver_name
    FROM phone_calls
    JOIN people receiver ON receiver.phone_number = phone_calls.receiver
    JOIN people caller ON caller.phone_number = phone_calls.caller
    WHERE caller.name = 'Bruce'
        AND phone_calls.duration < 60
        AND phone_calls.day = 28
        AND phone_calls.month = 7
        AND phone_calls.year = 2023;
