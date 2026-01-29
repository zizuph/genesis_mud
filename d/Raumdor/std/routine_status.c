/* This is to avoid requiring an #include of a file in a fixed location
 * in child objects (since that reduces portability) and I don't
 * know a better way to do it. Suggestions welcome.
 */
mapping STATUS = ([
    "CANCELLED" : -1,
    "SUCCESS"   :  0,
    "FAILURE"   :  1,
    "ERROR"     :  2,
    "BLOCKED"   :  3,
]);
