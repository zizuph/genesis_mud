#define ALCHEMY_DIR "/d/Faerun/alchemy/"
#define ALCHEMY_PRODUCT_DIR "/d/Faerun/alchemy/products/"

#define LARGE_CRAFTING_LOG(x,y)  write_file(ALCHEMY_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )
                                
#define PUSHY_DIED_LOG(x,y)  write_file(ALCHEMY_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )
