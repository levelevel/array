//動的配列（アレイ）
//
//## 機能
//- データ：任意のポインタ
//- 追加・削除・複製・push・pop

//ポインタ版動的配列
typedef struct array {
    int num;
    int capacity;
    void **buckets;
} array_t;

//int版動的配列
typedef struct iarray {
    int num;
    int capacity;
    int *buckets;
} iarray_t;


//アレイをアロケートする。
array_t *new_array(int size);

//アレイを開放する。
void free_array(array_t *array);

//アレイのサイズ(array->num)を取得する。
int num_array(const array_t *array);

//アレイのサイズを設定する。アレイのサイズは自動的に拡張される。
void set_array_size(array_t *array, int size);

//アレイのidx番目にデータを格納する。アレイのサイズは自動的に拡張される。
//データ未設定の領域にはNULLが設定される。
void put_array(array_t *array, int idx, void *data);

//アレイのidx番目のデータを取得する。アレイのサイズは変わらない。
void *get_array(const array_t *array, int idx);

//アレイのidx番目のデータを削除する。以降のデータは前に詰められる。アレイのサイズは1減る。
void del_array(array_t *array, int idx);

//アレイの最後にデータを1個追加する。アレイのサイズは1増える。
void push_array(array_t *array, void *data);

//アレイの最後のデータを1個取り出す。アレイのサイズは1減る。
void *pop_array(array_t *array);

//アレイを複製する。
array_t *dup_array(array_t *array);


//データがint版（未実装）
iarray_t *new_iarray(int size);
void free_iarray(iarray_t *array);
int num_iarray(const iarray_t *array);
void put_iarray(iarray_t *array, int idx, int data);
int get_iarray(const iarray_t *array, int idx);
void del_iarray(iarray_t *array, int idx);
void push_iarray(iarray_t *array, int data);
int pop_iarray(iarray_t *array);
iarray_t *dup_iarray(iarray_t *array);
