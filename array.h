//動的配列
//
//## 機能
//- データ：任意のポインタ・整数
//- 追加・削除・複製・push・pop

typedef struct array {
    int num;
    int capacity;
    void **buckets;
} array_t;

typedef struct iarray {
    int num;
    int capacity;
    int *buckets;
} iarray_t;


array_t *new_array(int size);
void  free_array(array_t *array);
int   num_array (array_t *array);
void  put_array (array_t *array, int idx, void *data);
void *get_array (array_t *array, int idx);
void  del_array (array_t *array, int idx);
void  push_array(array_t *array, void *data);
void *pop_array (array_t *array);
array_t *dup_array(array_t *array);

iarray_t *new_iarray(int size);
void free_iarray(iarray_t *array);
int  num_iarray (iarray_t *array);
void put_iarray (iarray_t *array, int idx, int data);
int  get_iarray (iarray_t *array, int idx);
void del_iarray (iarray_t *array, int idx);
void push_iarray(iarray_t *array, int data);
int  pop_iarray (iarray_t *array);
iarray_t *dup_iarray(iarray_t *array);
