# Images names
BASE_NAME = wt:wt
FRONT_NAME = wt:frontend
BACK_NAME = wt:backend

# Building the images
build: wt-build frontend-build backend-build
	docker compose up

frontend-build: wt-build
	docker build -t $(FRONT_NAME) -f frontend/Dockerfile .

backend-build: wt-build
	docker build -t $(BACK_NAME) -f backend/Dockerfile .

wt-build:
	docker build -t $(BASE_NAME) .