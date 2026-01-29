#ifndef PERSISTENT_OBJECT_MANAGER_HEADER
#define PERSISTENT_OBJECT_MANAGER_HEADER

#define PERSISTENT_OBJECT_MANAGER \
    "/d/Emerald/sys/global/persistent_object_manager"

#define POM_ADD(ob, room, subl) \
    PERSISTENT_OBJECT_MANAGER->add_persistent_object(ob, room, subl)

#define POM_REMOVE(id, room) \
    PERSISTENT_OBJECT_MANAGER->remove_persistent_object(id, room)

#define POM_LOAD(room) \
    PERSISTENT_OBJECT_MANAGER->load_persistent_objects(room)

#define POM_GET_ID(ob) \
    (ob->query_prop(PERSISTENT_OBJECT_ID))

#define POM_SAVE_DIR "/d/Emerald/log/persistent_object/"

#define PERSISTENT_OBJECT_FILE(r) (POM_SAVE_DIR + r[11..])

#define PERSISTENT_OBJECT_LIST       "persistent_objects"
#define PERSISTENT_OBJECT_LIST_ID    0
#define PERSISTENT_OBJECT_LIST_FILE  1
#define PERSISTENT_OBJECT_LIST_SUBL  2
#define PERSISTENT_OBJECT_LIST_SIZE  3

#define PERSISTENT_OBJECT_ID "_em_persistent_object_id"

#endif
