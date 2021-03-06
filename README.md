OpenCV2
=======

l 구현의 목적:
- Normalized correlation 방법으로 template matching을 구현하고 얼굴영상 DB에서 내 얼굴을찾는다.
- 얼굴영상 DB는 USB 또는 디지털카메라를 이용하여 내얼굴과 친구들 얼굴의 영상을 저장하여 사용한다.
- 최소 10장의 얼굴영상을 파일로 저장한다.
- 내얼굴 영상을 한 장 더 획득하고 얼굴영상 DB에 있는 내얼굴 영상과의 correlation 계수값이 가장높게 나오는지 확인한다.
l 구현 방법
1) USB 또는 디지털 카메라를 이용하여 얼굴영상 DB를 생성한다. 내얼굴과 친구얼굴을 포함하여 최소10장을 획득한다. 10장 이상 획득도 가능함. 하나의 얼굴 영상은 아래와 같은 크기로 정한다. (다른
크기도 가능하나 크기가 너무 크면 연산 시간이 많이 걸림. 모든 얼굴 영상이 동일한 크기를 가지면됨) 정사각형의 형태로 얼굴영상을 임의의 크기로 자른 다음 확대/축소하여도 가능하다. 또한 흑백영
상으로 저장한다.

120*120크기의 이미지 사용.

2) 얼굴영상 DB 생성시 주의점
- template matching은 영상의 위치에 민감하므로 얼굴들의 눈, 코, 입의 위치가 비슷하여야 한다.
- 따라서, 영상의 상단은 눈썹에, 하단은 아랫입술에 맞춘다. 아랫입술을 포함하여도 120크기가 남는다면 턱부분을 일부 포함할 수도 있다. 코는 x축 기준으로 중앙에 오도록 한다.
- 영상의 좌,우는 눈썹 가장자리 끝부분에 최대한 맞춘다.

3) 각 얼굴영상은 따로 파일로 저장하고 파일명은 C 프로그램에서 open하기 용이하게 구분한다.
