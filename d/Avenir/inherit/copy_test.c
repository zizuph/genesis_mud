inherit "/d/Avenir/inherit/copy_file";

void
do_copy()
{
    setuid();
    seteuid(getuid());

    copy_file("/d/Avenir/union/sway/visions/first_vision",
        "/d/Avenir/union/sway/visions/foobar");
}
