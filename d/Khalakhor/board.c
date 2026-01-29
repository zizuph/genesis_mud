#pragma strict_types

inherit "/std/board";

public varargs int
block_reader(int note = 0)
{
    return 1;
}

public int
block_writer()
{
    return 1;
}

public varargs int
allow_remove(int note)
{
   return 1;
}
