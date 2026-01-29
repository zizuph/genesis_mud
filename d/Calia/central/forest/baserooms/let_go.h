// Function:  let_go(go)

/*

Purpose:  fall from a tree.  FOR TESTING PURPOSES ONLY!

Arguments:  string, must be "go".

Returns: 0/1.

*/

int
let_go(string go)

    {

    object ob;
    if (go != "go") return 0;

    ob = clone_object(FOREST_FALLING_OBJECT);

    ob->move(this_player());
    ob->start_falling();

    return 1;

    }
