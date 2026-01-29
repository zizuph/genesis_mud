/*
 * This module can be inherited to provide support functions for a sorted list.
 *
 * There are still a large number of possible improvements here to decrease
 * the number of memory allocations but its still better than what was done
 * in the AoD master.
 *
 * - Cotillion, 2020
 */

#define LIST_VAL_FUNC      (0)
#define LIST_KEY_FUNC      (1)
#define LIST_COMPARATOR    (2)
#define LIST_VALUES        (3)
#define LIST_ITEMS         (4)

/*
 * Function name: init_sorted_list
 * Arguments:  function sort_func - The comparator to use for sorting the
 *                                      list. Same as sort_array
 *             function val_func  - A function called on each entry/key
 *                                  to get a value for the comparator.
 *                                  (if not specified the entry is used)
 *             function key_func  - A function applied to the entry to get
 *                                  an unique id for the object. This is
 *                                  needed if == can't be used to compare
 *                                  the entries. For example when they are
 *                                  arrays or mappings which are recreated between
 *                                  calls.
 * Returns A reference to the list, used as input in other calls
 */
 mixed
 init_sorted_list(function sort_func, function val_func = 0, function key_func = 0)
 {
    return ({
        val_func,
        key_func,
        sort_func,
        ({ }),
        ({ })
    });
}

static int
binary_search(mixed list, mixed val)
{
    mixed *items = list[LIST_ITEMS];
    function cmp = list[LIST_COMPARATOR];

    int l = 0;
    int r = sizeof(items) - 1;

    if (r < 0)
        return 0;

    while (l <= r) {
        int middle = (l + r) / 2;
        int res = cmp(val, list[LIST_VALUES][middle]);

        if (res > 0) {
            l = middle + 1;
        } else if (res < 0) {
            r = middle - 1;
        } else {
            return middle;
        }
    }

    /* Not found, insertion point */
    return -l;
}

static int
wrapped_cmp(function cmp, mixed a, mixed b) {
    return cmp(a[1], b[1]);
}

/*
 * Function name: sorted_list_set
 * Description  : Sets the contents of the list and sorts it.
 *                This is faster than individually adding the entries.
 */
void
sorted_list_set(mixed list, mixed *entries)
{
    function keyfunc = list[LIST_KEY_FUNC];
    function valfunc = list[LIST_VAL_FUNC];
    function cmp = list[LIST_COMPARATOR];

    mixed *keys = entries;
    if (keyfunc) {
        keys = map(entries, keyfunc);
    }

    mixed vals = entries;
    if (valfunc) {
        vals = map(keys, valfunc);
    }

    mixed *pair_list = allocate(sizeof(keys));
    for (int i = 0; i < sizeof(pair_list); i++) {
        pair_list[i] = ({ keys[i], vals[i] });
    }

    sort_array(pair_list, &wrapped_cmp(cmp, ));

    list[LIST_VALUES] = map(pair_list, &operator([])(, 1));
    list[LIST_ITEMS] = map(pair_list, &operator([])(, 0));
}

/*
 *  Function name: sorted_list_add
 *  Description  : Adds a new entry to a list.
 */
int
sorted_list_add(mixed list, mixed entry)
{
    mixed key = entry;
    function keyfunc = list[LIST_KEY_FUNC];
    if (keyfunc) {
        key = keyfunc(entry);
    }

    mixed val = entry;
    function valfunc = list[LIST_VAL_FUNC];
    if (functionp(valfunc)) {
        val = valfunc(entry);
    }

    // Find the insertion position
    int pos = abs(binary_search(list, val));
    list[LIST_VALUES] = include_array(list[LIST_VALUES], ({ val }), pos);
    list[LIST_ITEMS] = include_array(list[LIST_ITEMS], ({ key }), pos);
    return pos;
}

/*
 * Function name: sorted_list_remove
 * Description  : Removes an entry from the list.
 */
int
sorted_list_remove(mixed list, mixed entry)
{
    mixed key = entry;
    function keyfunc = list[LIST_KEY_FUNC];
    if (keyfunc) {
        key = keyfunc(entry);
    }

    int pos = member_array(key, list[LIST_ITEMS]);
    if (pos >= 0) {
        list[LIST_VALUES] = exclude_array(list[LIST_VALUES], pos, pos);
        list[LIST_ITEMS] = exclude_array(list[LIST_ITEMS], pos, pos);
        return pos;
    }

    return -1;
}

/*
 * Function name: sorted_list_update
 * Description  : Called to update an entry in the list. Will check if the
 *                value actually changed and if so move the element.
 */
int
sorted_list_update(mixed list, mixed entry)
{
    function keyfunc = list[LIST_KEY_FUNC];
    function cmp = list[LIST_COMPARATOR];

    mixed key = entry;
    if (keyfunc) {
        key = keyfunc(entry);
    }

    // Does it actually exist in the list?
    int pos = member_array(key, list[LIST_ITEMS]);
    if (pos < 0) {
        return -1;
    }

    mixed cur_val = list[LIST_VALUES][pos];

    mixed val = entry;
    function valfunc = list[LIST_VAL_FUNC];
    if (functionp(valfunc)) {
        val = valfunc(entry);
    }

    // There was no change in value, no update needed.
    if (cmp(val, cur_val) == 0) {
        return pos;
    }

    // If the new position returned is our current position (before),
    // or the position after we don't actually need to a move just update
    // the value.
    int new_pos = abs(binary_search(list, val));
    if (pos == new_pos || (pos + 1) == new_pos)
    {
        list[LIST_VALUES][pos] = val;
        return pos;
    }

    /* TODO: Replace with actually swapping elements instead of reallocating
     * the entire list. */
    sorted_list_remove(list, entry);
    return sorted_list_add(list, entry);
}

/*
 * Function name: sorted_list_get
 * Description  : Get the sorted list of keys from the list.
 */
mixed *
sorted_list_get(mixed list)
{
    return list[LIST_ITEMS];
}

/*
 * Function name: sorted_list_get_position
 * Description  : Returns the position of an entry. 0 indexed.
 */
mixed
sorted_list_get_position(mixed list, mixed entry) {
    mixed key = entry;
    function keyfunc = list[LIST_KEY_FUNC];
    if (keyfunc) {
        key = keyfunc(entry);
    }

    return member_array(key, list[LIST_ITEMS]);
}

static int
val(mixed entry)
{
    return entry;
}

static int
cmp(int a, int b)
{
    if (a > b)
        return 1;
    if (a == b)
        return 0;
    return -1;
}

void
test_sorted_list()
{
    mixed list = init_sorted_list(cmp, &operator([])(, "1"), &operator([])(, "name"));
    //mixed list = init_sorted_list(cmp, &operator(+)(, 10));
    //sorted_list_set(list, ({ 1, 100, 5, 10, 20 }));
    // sorted_list_add(list, 9);
    // sorted_list_add(list, 5);
    // sorted_list_add(list, -1);
    // sorted_list_add(list, 6);

    sorted_list_add(list, ([ "1": 5, "name": "a"  ]));
    sorted_list_add(list, ([ "1": 10, "name": "b" ]));
    sorted_list_add(list, ([ "1": 20, "name": "c" ]));
    sorted_list_update(list, ([ "1": 21, "name": "b" ]));
    dump_array(list);
}