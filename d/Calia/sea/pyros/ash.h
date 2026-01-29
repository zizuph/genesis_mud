
int
do_collect(string str)
{
    object ash;
    int num;

    if (str != "ash")
    {
        NF("What?\n");
        return 0;
    }
    ash = clone_object("/d/Calia/walkers/fire/objects/ash");
    num = 3 + random(6);
    ash->set_heap_size(num);
    ash->move(TP,1);
    write("You collect "+num+" handfuls of ash from around the flame.\n");
    say(QCTNAME(TP)+" collects some ash from ground.\n");
    return 1;
}
