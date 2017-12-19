pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh 'rm -rf build'
                sh 'mkdir build'
                sh 'cd build && cmake ..'
                sh 'cd build && make'
            }
        }
        stage('Test') {
            steps {
                timeout(20) {
                    sh 'cd build && make test'
                }
            }
        }
    }
}
