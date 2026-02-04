/* Created by Lucas
 * November 1995
 */

inherit "/std/room";

create_room()
{
    set_short("Voice training studio.");
    set_long("This rather large studio is where some of the " +
             "world's greatest singers come to train with the " +
             "master.  Many accomplished and talented students " +
             "have taken their voice lessons here.  Hymns, arias " +
             "and many voice solos are visible on the music stands " +
             "around the room.  Perhaps you could persuade the fine " +
             "minstrel to teach you a thing or two.\n");

    add_item(({"hymns","arias","solos","music"}),
             "The music has been collected over the years by " +
             "the master.  It is quite a diverse and challenging " +
             "repertoire.\n");

    add_item(({"music stand","music stands","stand","stands"}),
             "The brass stands are set at various heights in " +
             "order to suit the many sizes of students that " +
             "use them.\n");
}

