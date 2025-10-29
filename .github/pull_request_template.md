name: Feature
description: Propose a merge request of a new feature.

labels:
  - feature
reviewers:
  - hozlucas28

title: "Feature: "

body:
  - type: markdown
    attributes:
      value: |
        Thanks for taking the time to develop a new feature! Please fill out the template below as best as you can.

  - type: textarea
    id: feature-value
    attributes:
      label: What value does this feature bring?
      description: Explain the value this feature will bring to the project.
      placeholder: This feature will...
    validations:
      required: true

  - type: textarea
    id: steps-to-try-it
    attributes:
      label: How can we test this feature?
      description: Provide a step-by-step list of how to test this feature.
      placeholder: |
        1. Do this...
        2. Then do that...
        3. Finally, check that...
    validations:
      required: true

  - type: dropdown
    id: environment
    attributes:
      label: In which environments did you test this feature?
      description: Select the environments where you tested this feature.
      options:
        - DevContainer
        - DevContainer (Docker Compose)
        - DevContainer (Docker Swarm)
        - Local machine
        - Local machine (Docker Compose)
        - Local machine (Docker Swarm)
      default: 0
      multiple: true
    validations:
      required: true
