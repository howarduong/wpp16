������߿��԰��������� WDF �ļ�.
������������һ�� filename.lst ���ļ�.
ÿһ��д��һ�����·�������ļ���
�� wdfpck filename
�Ϳ��Դ���� filename.wdf
(���� lst �ļ��������, ������ wdfpck x filename �⿪��)

�ڳ�����, �� WFile::OpenDataFile("filename.wdf");
�Ϳ��Դ�.
�Ժ� WFile::Open("filename/xxxx");
�Ϳ��Դ� filename.wdf ��� xxxx �ļ�
ע��, ����ֻ���� / ��������\\, ��һ�� / ����Ϊ�����ļ������ļ��ķָ��.
���� WFile::Open("path\\datafile/xxxx"); ����д

��Ȼ, ������� path\filename\xxxx ����ļ�, �����ȴ�����ļ�, ���������ݰ����.
