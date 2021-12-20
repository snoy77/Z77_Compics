import vk_api
import WIA
from vk_api.longpoll import VkLongPoll, VkEventType
import serial

vk_session = vk_api.VkApi(token=WIA.TOKEN)
sesion_api = vk_session.get_api()
long_pull = VkLongPoll(vk_session)

#ну и дичь
s = serial.Serial('COM4')
res = s.readline()
res = res.decode("Ascii")
print(res)
s.write(b'start bot')
#------------------------------


def getUserName(id):
	r = vk_session.method('users.get', {'user_ids': id})[0]
	return str(str(r['id']) + " " + r['first_name'] + " " + r['last_name'])
for event in long_pull.listen():
     
     if event.type == VkEventType.MESSAGE_NEW:
          if event.to_me:
               user_id = event.user_id
               message = event.text.lower()
               message = "-> mes: \"" + message + "\""
               s.write(bytes(message, 'utf-8'))
               print(getUserName(user_id) + ": \"" + event.text + "\"")

