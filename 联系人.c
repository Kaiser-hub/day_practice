#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//������ϵ�˵Ľṹ�壬���������͵绰����
typedef struct PersonInfo {
	char name[256];
	char sex[32];
	char age[32];
	char phone[256];
	char address[256];
}PersonInfo;

//��һ����ϵ�˽���Ľṹ�壬������ϵ���ܸ�������Ч����
//[0,size)�������ЧԪ�أ�[size,Total)����ЧԪ��
typedef struct AddressBook{
	PersonInfo* person;
	int size;
	int capacity;//����
}AddressBook;

//д�ļ�
void Save(AddressBook* addr_book) {
	FILE* fp = fopen("C:/Users/HP/source/repos/��ϵ��С����/text.txt", "w");
	if (fp == NULL) {
		perror("�ļ���ʧ��\n");
		return;
	}
	for (int i = 0; i < addr_book->size; i++) {
		fwrite(&addr_book->person[i], sizeof(PersonInfo), 1, fp);
	}
	fclose(fp);
	printf("����ɹ�\n");
}

//���ݺ���
void ReallocPersonInfo(AddressBook* address_book) {
	address_book->capacity += 20;
	PersonInfo* newpersons = (PersonInfo*)malloc(sizeof(PersonInfo) * address_book->capacity);
	memcpy(newpersons, address_book->person, address_book->size * sizeof(PersonInfo));
	free(address_book->person);
	address_book->person = newpersons;
}


//���ļ�
void Load(AddressBook* addr_book){
	FILE* fp = fopen("C:/Users/HP/source/repos/��ϵ��С����/text.txt", "r");
	if (fp == NULL) {
		perror("�ļ���ʧ��\n");
		return;
	}
	PersonInfo tmp = { 0 };
	while (1){
		int n = fread(&tmp, sizeof(PersonInfo), 1, fp);
		if (n < 1) {
			break;
		}
		if (addr_book->size >= addr_book->capacity) {
			ReallocPersonInfo(addr_book);
		}
		addr_book->person[addr_book->size] = tmp;
		addr_book->size++;
	}
	fclose(fp);
}

//��ʼ�������������е���ϵ����Ϣ���Ƚ��Գ�ʼ��
//����ĺ���������ʹ����ָ������ ��ԭ���ж�
//1.�ṹ����Ϊ��������ʱ����Ҫ���п������������ṹ��һ��ռ�õ��ڴ涼�Ƚϴ󣬲���д��ָ�����ͣ�������Ч�ļ��ٿ�������
//2.��ʼ���������ڲ���Ҫ�޸Ľṹ����������ݣ������ں����ڲ��޸ģ�ͬʱ��ҪӰ�쵽�ⲿ����ʱ��ָ�룬�൱������Ͳ���
void Init(AddressBook* addr_book) {
	addr_book->size = 0;
	addr_book->capacity = 30;
	addr_book->person = (PersonInfo*)malloc(addr_book->capacity * sizeof(PersonInfo));//��̬�����ڴ��С
	for (int i = 0; i < addr_book->capacity; i++) {
		strcpy(addr_book->person[i].name, "");
		strcpy(addr_book->person[i].sex, "");
		strcpy(addr_book->person[i].age, "");
		strcpy(addr_book->person[i].phone, "");
		strcpy(addr_book->person[i].address, "");
	}
}

int Print() {
	printf("========================\n");
	printf("1.�����ϵ��\n");
	printf("2.ɾ��ָ����ϵ��\n");
	printf("3.����ָ����ϵ��\n");
	printf("4.�޸�ָ����ϵ��\n");
	printf("5.��ʾ������ϵ��\n");
	printf("6.���������ϵ��\n");
	printf("0.�˳�����\n");
	printf("========================\n");
	printf("����������ѡ��\n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

//�����ϵ�˺���
void AddPersonInfo(AddressBook* address_book) {
	printf("������ϵ��!\n");
	if (address_book->size >= address_book->capacity) {
		//��ϵ����������������
		ReallocPersonInfo(address_book);
	}
	PersonInfo* info = &address_book->person[address_book->size];
	printf("������������ϵ�˵�������\n");
	scanf("%s", info->name);
	printf("������������ϵ�˵��Ա�\n");
	scanf("%s", info->sex);
	printf("������������ϵ�˵����䣺\n");
	scanf("%s", info->age);
	printf("������������ϵ�˵ĵ绰���룺\n");
	scanf("%s", info->phone);
	printf("������������ϵ�˵�סַ��\n");
	scanf("%s", info->address);
	address_book->size++;
	printf("~~������ϵ�˳ɹ���\n");
}

//ɾ��ָ����ϵ�˺���
void DelPersonInfo(AddressBook* address_book) {
	printf("ɾ��ָ����ϵ��\n");
	if (address_book->size <= 0) {
		printf("ͨѶ¼Ϊ�գ�����ʧ��\n");
		return;
	}
	printf("������Ҫɾ����ϵ�˵����:");
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= address_book->size) {
		printf("����������Υ��������ʧ��\n");
		return;
	}
	//��ȡ���һ��Ԫ��
	PersonInfo* last_info = &address_book->person[address_book->size-1];
	//��ȡ��ɾ����Ԫ��
	PersonInfo* delete_info = &address_book->person[id];
	*delete_info = *last_info;
	address_book->size--;
	printf("ָ����ϵ��ɾ���ɹ���\n");
}

//����ָ����ϵ�˺���
void FindPersonInfo(AddressBook* address_book) {
	//������ҵ���ϵ�˴����������������ʾ������������ϵ��
	printf("����ָ����ϵ��\n");
	printf("����������Ҫ������ϵ�˵�����\n");
	char name[256] = { 0 };
	scanf("%s", name);
	for (int i = 0; i < address_book->size; i++) {
		PersonInfo* find_info = &address_book->person[i];
		if (strcmp(name, find_info->name) == 0) {
			printf("[%d] %s: %s, %s, %s, %s\n", i, find_info->name, find_info->sex, find_info->age, find_info->phone, find_info->address);
		}
	}
	printf("��ʾ������ϵ������\n");
}

//�޸�ָ����ϵ�˺���
void ModifyPersonInfo(AddressBook* address_book) {
	printf("�޸�ָ����ϵ����Ϣ\n");
	printf("��������Ҫ�޸���ϵ�˵���ţ�\n");
	if (address_book->size <= 0) {
		printf("ͨѶ¼Ϊ�գ�����ʧ��\n");
		return;
	}
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= address_book->size) {
		printf("����������Υ��������ʧ��\n");
		return;
	}
	PersonInfo* info = &address_book->person[id];
	printf("�������޸ĺ����Ϣ(*��ʾ������޸�)\n");
	printf("������");
	char name[256] = { 0 };
	scanf("%s", name);
	if (strcmp(name, "*") != 0) {
		strcpy(info->name, name);
	}
	printf("�Ա�");
	char sex[32] = { 0 };
	scanf("%s", sex);
	if (strcmp(sex, "*") != 0) {
		strcpy(info->sex, sex);
	}
	printf("���䣺");
	char age[32] = { 0 };
	scanf("%s", age);
	if (strcmp(age, "*") != 0) {
		strcpy(info->age, age);
	}
	printf("�绰��");
	char phone[256] = { 0 };
	scanf("%s", phone);
	if (strcmp(phone, "*") != 0) {
		strcpy(info->phone, phone);
	}
	printf("סַ��");
	char address[256] = { 0 };
	scanf("%s", address);
	if (strcmp(address, "*") != 0) {
		strcpy(info->address, address);
	}
	printf("�޸ĳɹ���\n");
}

//��ʾ������ϵ�˺���
void ShowPersonInfo(AddressBook* address_book) {
	printf("��ʾ������ϵ��\n");
	//����������֮���˳����ʾ
	PersonInfo ret = { "\0" };
	for (int i = 0; i < address_book->size; i++) {
		PersonInfo* info = &address_book->person[i];
		for (int j = i + 1; j < address_book->size; j++) {
			PersonInfo* info1 = &address_book->person[j];
			if (strcmp(info->name, info1->name) > 0) {
				ret = *info;
				*info = *info1;
				*info1 = ret;
			}
		}
	}
	for (int a = 0; a < address_book->size; a++) {
		PersonInfo* info = &address_book->person[a];
		printf("[%d] %s: %s, %s, %s, %s\n", a, info->name, info->sex, info->age, info->phone, info->address);
	}
	printf("��ǰ����ʾ%d����¼\n", address_book->size);
}

//���������ϵ�˺���
void ClearPersonInfo(AddressBook* address_book) {
	printf("���������ϵ��\n");
	printf("�����ȷ��Ҫ���������ϵ����Yes/No\n");
	char choice[32] = { 0 };
	scanf("%s", choice);
	if (strcmp(choice, "Yes") == 0 || strcmp(choice, "yes") == 0) {
		address_book->size = 0;
		printf("�����ϣ�\n");
		return;
	}
	else {
		printf("��ղ�����ȡ��\n");
		return;
	}
}

int main() {
	AddressBook address_book;
	Init(&address_book);
	Load(&address_book);
	typedef void(*Func)(AddressBook*);
	Func func_table[] = {
		NULL,//����Ӹ�NULL����Ϊ���뺯��Print()�е�ѡ�����Ŷ�Ӧ��
		AddPersonInfo,
		DelPersonInfo,
		FindPersonInfo,
		ModifyPersonInfo,
		ShowPersonInfo,
		ClearPersonInfo
	};
	while (1) {
		int choice = Print();
		if (choice < 0 || choice >= sizeof(func_table) / sizeof(func_table[0])) {
			printf("�������벻�Ϸ�\n");
			continue;
		}
		if (choice == 0) {
			Save(&address_book);
			printf("�ټ���\n");
			break;
		}
		func_table[choice](&address_book);
	}
	return 0;
}
