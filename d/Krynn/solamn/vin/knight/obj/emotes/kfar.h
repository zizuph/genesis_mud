/*
 * Emote:       kfar
 * Description: Sylvana stiffly bids farewell and prepares to depart.
 *
 *              After idea from Sylvana Knight of the Crown
 *
 */
int
kfar(string str)
{
    object *oblist;

    if (TP->query_knight_level() == 2 && !str)
    {
        write("You stiffly bid farewell and prepare to depart.\n");
        all(" stiffly bids farewell and prepares to depart.");
        return 1;
    }

    NF("Stiff farewell to whom?\n");

    if (!str)
    {
        write("You nobly bid farewell and prepare to depart.\n");
        all(" nobly bids farewell and prepares to depart.");
        return 1;
    }

    oblist = parse_this(str, "[to] [the] %l");
    if (!sizeof(oblist))
        return 0;

    if (TP->query_knight_level() == 2)
    {
        if (sizeof(oblist) == 1 && oblist[0]->query_knight_level() > 2)
        {
            actor("You respectfully bid farewell to",
              oblist, " and prepare to depart.");
            target(" respectfully bids farewell to you and prepares "+
              "to depart.", oblist);
            all2act(" respectfully bids farewell to ", oblist, " and "+
              "prepares to depart.");
            return 1;
        }
        actor("You stiffly bid farewell to",
          oblist, " and prepare to depart.");
        target(" stiffly bids farewell to you and prepares "+
          "to depart.", oblist);
        all2act(" stiffly bids farewell to ", oblist, " and "+
          "prepares to depart.");

        return 1;
    }

    actor("You nobly bid farewell to", oblist, " and prepare" +
      " to depart.");
    target(" nobly bids farewell to you and prepares "+
      "to depart.", oblist);

    all2act(" nobly bids farewell to ", oblist, " and prepares" +
      " to depart.");
    return 1;
}



