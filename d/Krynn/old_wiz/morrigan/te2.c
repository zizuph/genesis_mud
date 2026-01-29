inherit "/std/object";

create_object()
{
    int a;

    for (a = 0; a < 1000; a++)
	clone_object("/d/Krynn/morrigan/te");
}
