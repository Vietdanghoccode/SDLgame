Họ và tên: Nguyễn Khánh Việt
MSV: 23020171
Game của em là pacman. Gồm có pacman và 4 con ma như trong bản chơi gốc 
Pacman sẽ có nhiệm vụ là ăn các thức ăn màu vàng và né các con ma, khi pacman ăn những Power coin được random trên bản đồ 
mỗi 5 hạt nhỏ ăn đc thì nó có khả năng ăn đc những con ma và dễ thở hơn.
Ghost có 4 con ma mỗi con có 3 trạng thái:
Scatter: mỗi con ma sẽ đi về góc của nó
Chasing: mỗi con ma sẽ có 1 mục tiêu riêng :
        + blinky vẫn dí tới người chơi 
        + pinky nó sẽ căn cứ vào di chuyển và chặn đầu người chơi
        + inky đi tới vị trí đối xứng của inky qua pacman
        + clyde nếu pacman tới gần trong bán kính 8 ô thì nó sẽ lùa theo, còn không thì sẽ đi tới ô góc của nó
Frighten: lúc này mấy con ma sẽ sợ hãi, và đi ngược hướng lại, khi này nó có thể bị ăn bởi pacman

Kĩ thuật sử dụng:
-Sử dụng hàng đợi: stack, queue, kiểu dữ liệu nâng cao pair;
-Thuật toán dò đường của ma đã được dùng là bfs có cải tiến của em ạ.
-Có học được cách sử dụng SDL.h và SDL.image để render đồ hoạ và xử lý hoạt ảnh ạ.
-Có sử dụng tính kế thừa của Class.
-Ngoài ra em cũng tự học được cách làm menu, phần âm thanh em có cố nhưng nó bị lỗi access violence và báo lỗi
khá khó hiểu nên em chưa thể có âm thanh được ạ.
-Sử dụng tickManager() để kiểm soát thời gian.

Em nghĩ mình nằm trong khoảng 8-8.5 điểm ạ.





