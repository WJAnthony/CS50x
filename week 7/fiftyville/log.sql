-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Finding the description of the crime that happened
SELECT description
FROM crime_scene_reports
WHERE year = '2023'
AND month = '7'
AND day = '28'
AND street = 'Humphrey Street';
-- 3 witnesses were interviewed and all mentioned the bakery, Theft took place at 1015am

-- Interview transcripts
SELECT transcript
FROM interviews
WHERE year = '2023'
AND month = '7'
AND day = '28';
-- Interviewee 1: Within 10 mins of the theft, Thief got into a car in the bakery parking lot and drove away
-- Interviewee 2: Recoginised the thief withdrawing money from the ATM on Leggett Street in the morning
-- Interviewee 3: After leaving bakery, Thief called someone for less than 1 min. Thief asked the person to purchase tix for the earliest flight the next day (29 July 2023)

-- Finding the list of account_number the theif could have
SELECT account_number, amount
FROM atm_transactions
WHERE year = '2023'
AND month = '7'
AND day = '28'
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Finding first list of suspects for the Thief using bank account numbers
SELECT name
FROM people
WHERE id in
    (SELECT person_id
     FROM bank_accounts
     WHERE account_number in
        (SELECT account_number
         FROM atm_transactions
         WHERE year = '2023'
         AND month = '7'
         AND day = '28'
         AND atm_location = 'Leggett Street'
         AND transaction_type = 'withdraw'));
-- First list of suspects(Thief): Kenny, Iman, Benista, Taylor, Brooke, luca, Diana, Bruce

-- Finding second list of suspects(Thief) using phone calls
SELECT name
FROM people
WHERE phone_number in
    (SELECT caller
     FROM phone_calls
     WHERE year = '2023'
     AND month = '7'
     AND day = '28'
     AND duration < 60);
-- list: Kenny, Sofia, Benista, Taylor, Diana, Kelsey, Bruce, Carina
-- Updated list of suspects(thief): Kenny, Benista, Diana, Taylor, Bruce

-- Finding first list of suspects(accomplice) using phone calls
SELECT name, phone_number
FROM people
WHERE phone_number in
    (SELECT receiver
     FROM phone_calls
     WHERE year = '2023'
     AND month = '7'
     AND day = '28'
     AND duration < 60);
-- First list of suspects(accomplice): James, Larry, Anna, Jack, Melissa, Jacqueline, Philip, Robin, Doris

-- Finding Fiftyville's airport name
SELECT id, abbreviation, full_name
FROM airports
WHERE city = 'Fiftyville';
-- id: 8, abbreviation: CSF, full name: Fiftyville Regional Airport

-- Finding first flight out of fiftyville on the 29 July 2023
SELECT id, destination_airport_id, hour, minute
FROM flights
WHERE year = '2023'
AND month = '7'
AND day = '29'
AND origin_airport_id = '8'
ORDER BY hour, minute
LIMIT 1;
-- id: 36, destination airport id: 4, time: 0820

-- Finding city thief escaped to
SELECT id, abbreviation, full_name, city
FROM airports
WHERE id = '4';
-- Thief escaped to: New York City

-- Finding third list of suspects(Thief) using flights
SELECT name
FROM people
WHERE passport_number in
    (SELECT passport_number
     FROM passengers
     WHERE flight_id = '36');
-- People on this flight: Kenny, Sofia, Taylor, Luca, Kelsey, Edward, Bruce, Doris
-- Updated list of suspects(thief): Kenny, Taylor, Bruce

-- Finding fourth list of suspects(Thief) using car license plate
SELECT name, people.license_plate, hour, minute, activity
FROM people
JOIN bakery_security_logs on bakery_security_logs.license_plate = people.license_plate
WHERE name = 'Bruce'
AND year = '2023'
AND month = '7'
AND day = '28'
ORDER BY hour, minute;
-- Exited at 1018

SELECT name, people.license_plate, hour, minute, activity
FROM people
JOIN bakery_security_logs on bakery_security_logs.license_plate = people.license_plate
WHERE name = 'Taylor'
AND year = '2023'
AND month = '7'
AND day = '28'
ORDER BY hour, minute;
-- Exited at 1035
-- Since Bruce left at 1018, which is within 10 mins of crime, Bruce is the thief

-- Finding the accomplice
SELECT name, phone_number, caller, receiver
FROM people
JOIN phone_calls on phone_calls.caller = people.phone_number
WHERE name = 'Bruce'
AND year = '2023'
AND month = '7'
AND day = '28'
AND duration < 60;
-- Bruce called (375) 555-8161

SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';
-- Bruce called Robin, thus Robin is the accomplice
