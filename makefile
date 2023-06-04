# Images names
BASE_NAME = wt:latest
FRONT_NAME = wt:frontend
BACK_NAME = wt:backend

# Building the images
build: wt-latest wt-frontend wt-backend
	docker compose up

wt-frontend: wt-latest
	docker build -t $(FRONT_NAME) -f frontend/Dockerfile .

wt-backend: wt-latest
	docker build -t $(BACK_NAME) -f backend/Dockerfile .

wt-latest:
	docker build -t $(BASE_NAME) .

