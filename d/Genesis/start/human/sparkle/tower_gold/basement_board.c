inherit "/std/board";

int
block_writer()
{
    if (!this_interactive()->query_wiz_level())
    {
        return 0;
    }
 
    if (present(this_interactive(), environment()))
    {
        write("You are a wizard. Go make a fool of yourself elsewhere.\n");
    }

    return 1;
}
