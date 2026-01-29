/*
 *      s_laugh
 */

int
s_laugh(string str)
{
    if (!IS_SYBARITE(TP))
    {
        NF("You're not a Sybarite!\n");
        return 0;
    }        
        
    NF("Slaugh "+ str +" can't be done.\n");
    if (strlen(str))
        return 0;

    write("Ok.\n");
    allbb(" laughs the spine-chilling laugh of one who has known total "+
        "fear and no longer fears anything.");
    return 1;
}


