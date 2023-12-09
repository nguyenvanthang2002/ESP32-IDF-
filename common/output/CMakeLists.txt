set(app_scr outputvt.c)
set(pri_req "")
idf_component_register(SRCS ${app_scr}
                        INCLUDE_DIRS "."
                        REQUIRES ${pri_req})
