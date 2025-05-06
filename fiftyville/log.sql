-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Find the crime scene report for the theft
SELECT description
FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

SELECT name, transcript
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28;


+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- the flight was the earliest fligt on the next day.
-- Check bakery security logs on July 28, 2024
SELECT *
FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28;

| 259 | 2024 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
| 260 | 2024 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2024 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2024 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2024 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2024 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2024 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2024 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2024 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2024 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
| 269 | 2024 | 7     | 28  | 10   | 42     | entrance | NRYN856       |
| 270 | 2024 | 7     | 28  | 10   | 44     | entrance | WD5M8I6       |
| 271 | 2024 | 7     | 28  | 10   | 55     | entrance | V47T75I



-- Find ATM withdrawals on Leggett Street on July 28, 2024
SELECT *
FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2024 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2024 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2024 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2024 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2024 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2024 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2024 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2024 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
-- Find people who withdrew money from the ATM on Leggett Street on July 28, 2024
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2024 AND month = 7 AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';

  +---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+

-- Find people associated with the license plates from the bakery logs
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2024 AND month = 7 AND day = 28
      AND hour = 10
      AND minute BETWEEN 0 AND 59
      AND activity = 'exit'
);
+---------+
|  name   |
+---------+
| Vanessa |
| Barry   |
| Iman    |
| Sofia   |
| Taylor  |
| Luca    |
| Diana   |
| Kelsey  |
| Bruce   |
+---------+

-- Find names of callers and receivers for calls on July 28, 2024, with a duration of less than 60 seconds
SELECT caller.name AS caller_name, receiver.name AS receiver_name
FROM phone_calls
JOIN people AS caller ON phone_calls.caller = caller.phone_number
JOIN people AS receiver ON phone_calls.receiver = receiver.phone_number
WHERE year = 2024 AND month = 7 AND day = 28
  AND duration < 60;
  +-------------+---------------+
| caller_name | receiver_name |
+-------------+---------------+
| Sofia       | Jack          |
| Kelsey      | Larry         |
| Bruce       | Robin         |
| Kelsey      | Melissa       |
| Taylor      | James         |
| Diana       | Philip        |
| Carina      | Jacqueline    |
| Kenny       | Doris         |
| Benista     | Anna          |
+-------------+---------------+


-- Find the earliest flight departing Fiftyville on July 29, 2024
SELECT flights.id, city
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE year = 2024 AND month = 7 AND day = 29
ORDER BY hour, minute
LIMIT 1;

+----+---------------+
| id |     city      |
+----+---------------+
| 36 | New York City |
+----+---------------+

-- Find passengers on the earliest flight
SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = 36;

+--------+
|  name  |
+--------+
| Doris  |
| Sofia  |
| Bruce  |
| Edward |
| Kelsey |
| Taylor |
| Kenny  |
| Luca   |
+--------+

-- Find the accomplice for Bruce or Taylor
SELECT caller.name AS caller_name, receiver.name AS receiver_name
FROM phone_calls
JOIN people AS caller ON phone_calls.caller = caller.phone_number
JOIN people AS receiver ON phone_calls.receiver = receiver.phone_number
WHERE year = 2024 AND month = 7 AND day = 28
  AND duration < 60
  AND caller.name IN ('Bruce', 'Taylor');

