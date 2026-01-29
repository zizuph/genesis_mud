
int
do_collect(string str)
{
    object obsidian;
    int num;

    if (str != "obsidian")
    {
        NF("What?\n");
        return 0;
    }
    obsidian = clone_object("/d/Calia/walkers/fire/objects/obsidian");
    num = 3 + random(6);
    obsidian->set_heap_size(num);
    obsidian->move(TP,1);
    write("You collect "+num+" pieces of obsidian from the dust.\n");
    say(QCTNAME(TP)+" picks up a few pieces of rock from the ground.\n");
    return 1;
}
