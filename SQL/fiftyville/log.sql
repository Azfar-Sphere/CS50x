-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get the Crime Scene Report
SELECT
  *
FROM
  crime_scene_reports
WHERE
  YEAR = '2021'
  AND MONTH = '7'
  AND DAY = '28'
  AND street = 'Humphrey Street';

-- Id 295, 10:15am
-- Get the Interview
SELECT
  id,
  name,
  transcript
FROM
  interviews
WHERE
  YEAR = '2021'
  AND MONTH = '7'
  AND DAY = '28';

-- Interviewees: 161 Ruth, 162 Eugene, 163 Raymond,
-- Check for security footage from Bakery Parking Lot for Car
-- Within 10 Minutes in and Out
SELECT
  id,
  HOUR,
  MINUTE,
  activity,
  license_plate
FROM
  bakery_security_logs
WHERE
  YEAR = '2021'
  AND MONTH = '7'
  AND DAY = '28'
  AND HOUR = '10'
  AND MINUTE <= '25'
  AND MINUTE >= '15'
ORDER BY
  MINUTE ASC;

-- Possible Plates:
-- ID
-- Possible Plates
SELECT
  license_plate
FROM
  bakery_security_logs
WHERE
  id IN (260, 261, 262, 263, 264, 265, 266, 267);

--Possible Suspects
SELECT
  *
FROM
  people
WHERE
  license_plate IN (
    SELECT
      license_plate
    FROM
      bakery_security_logs
    WHERE
      id IN (260, 261, 262, 263, 264, 265, 266, 267)
  )
ORDER BY
  id;

-- Check withdrawl for ATM on Leggett Street
SELECT
  account_number
FROM
  atm_transactions
WHERE
  atm_location = 'Leggett Street'
  AND YEAR = '2021'
  AND MONTH = '7'
  AND DAY = '28'
  AND transaction_type = 'withdraw';

-- Possible People Based on Bank Accounts::
SELECT
  *
FROM
  people
WHERE
  id IN (
    SELECT
      person_id
    FROM
      bank_accounts
    WHERE
      account_number IN (
        SELECT
          account_number
        FROM
          atm_transactions
        WHERE
          atm_location = 'Leggett Street'
          AND YEAR = '2021'
          AND MONTH = '7'
          AND DAY = '28'
          AND transaction_type = 'withdraw'
      )
  )
ORDER BY
  id;

-- Possible People Based on Bank Accounts and Number Plate:
SELECT
  *
FROM
  bakery_security_logs
WHERE
  license_plate IN (
    SELECT
      license_plate
    FROM
      people
    WHERE
      id IN (
        SELECT
          person_id
        FROM
          bank_accounts
        WHERE
          account_number IN (
            SELECT
              account_number
            FROM
              atm_transactions
            WHERE
              atm_location = 'Leggett Street'
              AND YEAR = '2021'
              AND MONTH = '7'
              AND DAY = '28'
              AND transaction_type = 'withdraw'
          )
      )
  )
  AND YEAR = '2021'
  AND MONTH = '7'
  AND DAY = '28'
ORDER BY
  license_plate,
  HOUR,
  MINUTE;

-- Possible Plates:
-- Check for Call, Check for Earliest Flight out of Fiftyville Tomorrow
SELECT
  *
FROM
  phone_calls
WHERE
  duration < 60
  AND YEAR = '2021'
  AND MONTH = '7'
  AND DAY = '28';

-- Possible  Suspects:
SELECT
  *
FROM
  people
WHERE
  phone_number IN (
    SELECT
      caller
    FROM
      phone_calls
    WHERE
      duration < 60
      AND YEAR = '2021'
      AND MONTH = '7'
      AND DAY = '28'
  );

-- Possible Accomplices:
SELECT
  *
FROM
  people
WHERE
  phone_number IN (
    SELECT
      receiver
    FROM
      phone_calls
    WHERE
      duration < 60
      AND YEAR = '2021'
      AND MONTH = '7'
      AND DAY = '28'
  );

-- Flight
-- Get Airport Id
SELECT
  *
FROM
  airports
WHERE
  city = 'Fiftyville';

-- Get Flights
SELECT
  *
FROM
  flights
WHERE
  origin_airport_id IN (
    SELECT
      id
    FROM
      airports
    WHERE
      city = 'Fiftyville'
  )
  AND YEAR = '2021'
  AND MONTH = '7'
  AND DAY = '29'
ORDER BY
  HOUR ASC,
  MINUTE ASC;

-- Earliest Flight id 36, Destination 4
-- Get Passengers
SELECT
  *
FROM
  passengers
WHERE
  flight_id = '36';

-- Get Possible Suspects on Flight
SELECT
  *
FROM
  PEOPLE
WHERE
  passport_number IN (
    SELECT
      passport_number
    FROM
      passengers
    WHERE
      flight_id = '36'
  );

-- Check for Name Overlaps:
-- Between License Plate and Flights
SELECT
  name
FROM
  people
WHERE
  name IN (
    SELECT
      name
    FROM
      people
    WHERE
      passport_number IN (
        SELECT
          passport_number
        FROM
          passengers
        WHERE
          flight_id = '36'
      )
  )
  AND name IN (
    SELECT
      name
    FROM
      people
    WHERE
      license_plate IN (
        SELECT
          license_plate
        FROM
          bakery_security_logs
        WHERE
          id IN (260, 261, 262, 263, 264, 265, 266, 267)
      )
    ORDER BY
      id
  );

-- Sofia, Luca, Kelsey, Bruce
-- Between Flights and Calls
SELECT
  name
FROM
  people
WHERE
  name IN (
    SELECT
      name
    FROM
      people
    WHERE
      phone_number IN (
        SELECT
          caller
        FROM
          phone_calls
        WHERE
          duration < 60
          AND YEAR = '2021'
          AND MONTH = '7'
          AND DAY = '28'
      )
  )
  AND name IN (
    SELECT
      name
    FROM
      PEOPLE
    WHERE
      passport_number IN (
        SELECT
          passport_number
        FROM
          passengers
        WHERE
          flight_id = '36'
      )
  );

-- Kenny, Sofia, Taylor, Kelsey, Bruce
-- Compare this with Bank Transactions:
SELECT
  name
FROM
  people
WHERE
  name IN (
    SELECT
      name
    FROM
      people
    WHERE
      name IN (
        SELECT
          name
        FROM
          people
        WHERE
          phone_number IN (
            SELECT
              caller
            FROM
              phone_calls
            WHERE
              duration < 60
              AND YEAR = '2021'
              AND MONTH = '7'
              AND DAY = '28'
          )
      )
      AND name IN (
        SELECT
          name
        FROM
          PEOPLE
        WHERE
          passport_number IN (
            SELECT
              passport_number
            FROM
              passengers
            WHERE
              flight_id = '36'
          )
      )
  )
  AND name IN (
    SELECT
      name
    FROM
      people
    WHERE
      id IN (
        SELECT
          person_id
        FROM
          bank_accounts
        WHERE
          account_number IN (
            SELECT
              account_number
            FROM
              atm_transactions
            WHERE
              atm_location = 'Leggett Street'
              AND YEAR = '2021'
              AND MONTH = '7'
              AND DAY = '28'
              AND transaction_type = 'withdraw'
          )
      )
    ORDER BY
      id
  );

-- Kenny, Taylor, Bruce
-- Check with Licene Plates
SELECT
  name
FROM
  people
WHERE
  name IN (
    SELECT
      name
    FROM
      people
    WHERE
      license_plate IN (
        SELECT
          license_plate
        FROM
          bakery_security_logs
        WHERE
          id IN (260, 261, 262, 263, 264, 265, 266, 267)
      )
    ORDER BY
      id
  )
  AND name IN (
    SELECT
      name
    FROM
      people
    WHERE
      name IN (
        SELECT
          name
        FROM
          people
        WHERE
          name IN (
            SELECT
              name
            FROM
              people
            WHERE
              phone_number IN (
                SELECT
                  caller
                FROM
                  phone_calls
                WHERE
                  duration < 60
                  AND YEAR = '2021'
                  AND MONTH = '7'
                  AND DAY = '28'
              )
          )
          AND name IN (
            SELECT
              name
            FROM
              PEOPLE
            WHERE
              passport_number IN (
                SELECT
                  passport_number
                FROM
                  passengers
                WHERE
                  flight_id = '36'
              )
          )
      )
      AND name IN (
        SELECT
          name
        FROM
          people
        WHERE
          id IN (
            SELECT
              person_id
            FROM
              bank_accounts
            WHERE
              account_number IN (
                SELECT
                  account_number
                FROM
                  atm_transactions
                WHERE
                  atm_location = 'Leggett Street'
                  AND YEAR = '2021'
                  AND MONTH = '7'
                  AND DAY = '28'
                  AND transaction_type = 'withdraw'
              )
          )
        ORDER BY
          id
      )
  );

-- Bruce
-- Between Number Plates, Flights and Calls, Bruce is the Final Suspect
-- This means Accomplice is:
SELECT
  name
FROM
  people
WHERE
  phone_number IN (
    SELECT
      receiver
    FROM
      phone_calls
    WHERE
      caller IN (
        SELECT
          phone_number
        FROM
          people
        WHERE
          name = 'Bruce'
      )
      AND duration < 60
      AND YEAR = '2021'
      AND MONTH = '7'
      AND DAY = '28'
  );

-- Robin
-- City Escaped too Is:
SELECT
  city
FROM
  airports
WHERE
  id = 4;

-- New York City
-- | 161 | Ruth    | 2021 | 7     | 28  |
--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| 162 | Eugene  | 2021 | 7     | 28  |
--I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| 163 | Raymond | 2021 | 7     | 28  |
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |