/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 */

/*
 * /d/Genesis/cmd/soul_cmd_hobbit.c
 *
 * This is the soul command object for Hobbit. 
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/cmd/soul";

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 *
 * This function is outcommented while there are no special commands in it.
 *
mapping
query_cmdlist()
{
    return ::query_cmdlist();
}
 */

/* **************************************************************************
 * Here follows the actual functions. Please add new functions in the 
 * same order as in the function name list.
 * **************************************************************************/

int
giggle(string str)
{
    if (!strlen(str))
    {
        return ::giggle("mischievously");
    }
    else
    {
	return ::giggle(str);
    }
}

int
sing(string str)
{
    if (strlen(str))
    {
	return ::sing(str);
    }

    write("You sing a happy tune.\n");
    all(" sings a song of parties, food and merriment.");
    return 1;
}
