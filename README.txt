һ���򵥵�Http��ҳ������ʵ��

ʾ����վ www.dreamyouxi.com

��飺
	1.֧��GET����

	2.����winsock����

	3.֧���ļ�����

	4.֧���̳߳�

	5.֧��lua����д��̬��ҳ���ṩhttp����

	6.��վ�����԰�����litehttp��lua��дʵ��

	6.֧��lua����mysql����������չ�������ݿ�






��lua��дhttp������׽̳�:
	1.
		��server_config.lua ��� ���� ��ģ���ļ�ӳ����
		t["login"]="script/login"; --��ӷ���login ӳ�䵽"script/login.lua"
 
	2.
		������룺��doRequest�������Ǵ�������ĺ������ڲ��Զ����ã�pΪ���� ��table��
		�����ַ���Ϊ���ؿͻ��˵���Ϣ

		local t={};

		function t:doRequest(p)
			local name = p["name"];
			if name ==nil then
				return "��������"
			end
			if p["name"]=="��" then
				return   "�û�:"..name .." ��½ �ɹ� "   ;
			end
			return   "�û�:"..name .." ��½ ʧ�� "   ;
		end

		return t;

	3. 
		������ݿ� ֧�� ��Դ�ļ�ʾ�� ���԰�(MsgBoard.lua)
